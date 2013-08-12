#include<math.h>
#include<ctime>
#include<vector>
#include<fstream>
#include<sstream>

#define LEARNING_RATE 0.001
#define MOMENTUM 0.9
#define MAX_EPOCHS 1500
#define DESIRED_ACCURACY 90


class neuralNet{

private:
  double learningRate;
  double momentum;
  
  int nInput, nHidden, nOutput;
  
  double* inputNeurons;
  double* hiddenNeurons;
  double* outputNeurons;
  
  double** wInputHiddenCon;
  double** wHiddenOutputCon;
  
  long epoch;
  long maxEpochs;
  
  double desiredAccuracy;
  
  double** changeInputHiddenW;
  double** changeHiddenOutputW;
  
  double* hiddenErrorGrad;
  double* outputErrorGrad;
  
  double trainingSetAccuracy;
  double validationSetAccuracy;
  double generalizationSetAccuracy;
  double trainingSetMSE;
  double validationSetMSE;
  double generalizationSetMSE;

  bool useBatch;
  
  bool logResults;
  fstream logFile;
  int logResolution;
  int lastEpochLogged;

public:
  neuralNet(int n, int hidden, int out):
    nInput(n),nHidden(hidden),nOutput(out),epoch(0),logResults(false),
    logResolution(10),lastEpochLogged(-10),trainingSetAccuracy(0),
    validationSetAccuracy(0),generalizationSetAccuracy(0),
    trainingSetMSE(0),validationSetMSE(0),generalizationSetMSE(0)
  {
    inputNeurons = new double[in+1];
    for(int i=0;i<in;++i) inputNeurons[i]=0;
    inputNeurons[in] = -1;

    hiddenNeurons = new double[hidden+1];
    for(int i=0;i<hidden;++i) hiddenNeurons[i]=0;
    hiddenNeurons[hidden]=-1;
    
    outputNeurons = new double[out];
    for(int i=0;i<out;++i) outputNeurons[i]=0;

    wInputHiddenCon = new double*[in+1];
    for(int i=0;i<=in;++i){
      wInputHiddenCon[i] = new double[hidden];
      for(int j=0;j<hidden;++j) wInputHiddenCon[i][j] = 0;
    }

    wHiddenOputputCon = new double*[hidden+1];
    for(int i=0;i<=hidden;++i){
      wHiddenOutputCon[i] = new double[out];
      for(int j=0;j<out;++j) wHiddenOutputCon[i][j] = 0;
    }

    changeInputHiddenW = new double*[in+1];
    for(int i=0;i<=in;++i){
      changeInputHiddenW[i] = new double[hidden];
      for(int j=0;j<hidden;++j) changeInputHiddenW[i][j]=0;
    }

    changeHiddenOutputW = new double*[hidden+1];
    for(int i=0;i<=hidden;++i){
      changeHiddenOutputW[i] = new double[out];
      for(int j=0;j<out;++j) changeHiddenOutputW[i][j]=0;
    }

    hiddenErrorGrad = new double[hidden+1];
    for(int i=0;i<=hidden;++i) hiddenErrorGrad[i]=0;
    
    outputErrorGrad = new double[out+1];
    for(int i=0;i<=out;++i) outputErrorGrad[i] = 0;
    
    
    initializeWeights();
    learningRate = LEARNING_RATE;
    momentum = momentun;
    
    useBatch = false;
    maxEpochs = MAX_EPOCHS;
    desiredAccuracy = DESIRED_ACCURACY;
  }

  ~neuralNet(){
    delete[] inputNeurons;
    delete[] hiddenNeurons;
    delete[] outputNeurons;

    for(int i=0;i<=nInput;++i){ 
      delete[] wInputHiddenCon[i];
      delete[] changeInputHiddenW[i];
    }
    delete[] wInputHiddenCon;
    delete[] changeInputHiddenW;

    for(int i=0;i<nHidden;++i){
      delete[] wHiddenOutputCon[i];
      delete[] changeHiddenOutputW[i];
    }
    delete[] wHiddenOutputCon;
    delete[] changeHiddenOutputW;
    
    delete[] hiddenOutputGrad;
    delete[] inputHiddenGrad;
    
    if(logFile.is_open()) logFile.close();
  }

  void setLearningRate(double lr)
  {
    learningRate = lr;
  }
  
  void setMomentum (double m)
  {
    momentum = m;
  }

  void setMaxEpochs(int max)
  {
    maxEpochs = max;
  }

  void setDesiredAccuracy(float d)
  {
    desiredAccuracy = d;
  }
  
  void setBatchLearning(){useBatch=true;}
  
  void setStochasticLearning(){useBatch=false;}

  void resetWeights(){initializeWeights();}
  
  //write function for logging
  void enableLog(const char* filename, int resolution=1){}

  double* feedInput(double* inputs)
  {
    feedForward(inputs);
    return outputNeurons;
  }

  void trainNetwork(vector<dataEntry*> trainingSet, 
		    vector<dataEntry*> generalizationSet,
		    vector<dataEntry*> validationSet)
  {
    epoch =0;
    while((trainingSetAccuracy < desiredAccuracy || generalizationSetAccuracy < desiredAccuracy) && epoch < maxEpochs){
      double previousTAccuracy = trainingSetAccuracy;
      double previousGAccuracy = generalizationSetAccuracy;
      runTrainingEpoch(trainingSet);
      
      generalizationSetAccuracy = getSetAccuracy (generalizationSet);
      generalizationSetMSE = getSetMSE(generalizationSet);
      
      if(ceil(previousTAccuracy) != ceil(trainingSetAccuracy) || ceil(previousGAccuracy) != ceil(generalizationSetAccuracy)){
	std::cout<<"Epoch: "<<epoch
	    <<" Tset Accuracy: "<< trainingSetAccuracy<<" Tset MSE: "<<trainingSetMSE
		 <<" Gset Accuracy: "<<generalizationSetAccuracy<<" Gset MSE: "<<generalizationSetMSE<<std::endl;
      }
      
      epoch++;
    }
    
    validationSetAccuracy = getSetAccuracy(validationSet);
    validationSetMSE = getSetMSE(validationSet);
    
    std::cout<<"Training complete. Elapsed epochs: "<<epoch<<std::endl;
    std::cout<<"Validaiton Set Accuracy: "<<validationSetAccuracy<<std::endl;
    std::cout<<"Validation Set MSE: "<<validationSetMSE<<std::endl;
  }

private:
  
  void initializeWeights(){
    srand (unsigned int) time(0);
    
    for(int i=0; i<= nInput; ++i)
      for(int j=0;j<nHidden;++j){
	wInputHiddenCon[i][j]= (double) rand()/(RAND_MAX + 1)-0.5;
	changeInputHiddenW[i][j] = 0;
      }

    for(int i=0; i<= nHidden; ++i)
      for(int j=0; j < nOutput; ++j){
	wHiddenOutputCon[i][j] = (double) rand()/(RAND_MAX + 1) - 0.5;
	changeHiddenOutputW[i][j] = 0;
      }
  }

  void runTrainingEpoch(vector<dataEntry*> trainingSet){
    double incorrectPatterns = 0;
    double mse = 0;
    
    for(int tp=0;tp<(int) trainingSet.size();++tp){
      feedForward(trainingSet[tp]->pattern);
      backPropogate(trainingSet[tp]->target);

      bool patternCorrect = true;

      for(int k=0;k<nOutput;++k){
	if(getRoundedOutputValue(outputNeurons[k]) != trainingSet[tp]->target[k]) patternCorrect = false;
	mse += pow((outputNeuron[k] - trainingSet[tp]->target[k]), 2);
      }
      
      if(!patternCorrect) incorrectPatterns++;
    }

    if(useBatch) updateWeights();

    trainingSetAccuracy = 100 - (incorrectPattern/trainingSet.size() * 100);
    trainingSetMSE = mse/(nOutput*trainingSet.size());
  }

  void feedForward(double *inputs){
    for(int i=0;i<nInput;++i) inputNeurons[i] = inputs[i];

    for(int j=0;j<nHidden;++j){
      hiddenNeurons[j] = 0;
      
      for(int i=0;i<=nInput;++i) hiddenNeurons[j] += inputNeurons[i] * wInputHiddenCon[i][j];
      
      hiddenNeurons[j] = activationFunction(hiddenNeurons[j]);
    }
    
    for(int k=0;k<nOutput; ++k){
      outputNeurons[k] = 0;
      
      for(int j=0;j<=nHidden;++j) outputNeurons[k] += hiddenNeurons[j] * wHiddenOutputCon[j][k];

      outputNeurons[k] = activationFunction(outputNeurons[k]);
    }
  }

  void backpropagate(double* desiredValues){
    for(int k=0;k<nOutput;++k){
      outputErrorGrad[k] = getOutputErrorGrad(desiredValue[k], outputNeurons[k]);
      
      for(int j=0;j<=nHidden;++j)
	if(!useBatch)
	  changeHiddenOutputW[j][k] = learningRate* hiddenNeurons[j] * outputErrorGrad[k] + momentum*changeHiddenOutputW[j][k];
	else
	  changeHiddenOutputW[j][k] += learningRate* hiddenNeurons[j] * outputErrorGrad[k];
    }

    for(int j=0;j<nHidden;++j){
      hiddenErrorGrad[j] = getHiddenErrorGrad(j);
      
      for(int i=0;i<=nInput;++i)
	if(!useBatch)
	  changeInputHiddenW[i][j] = learningRate * inputNeurons[i]* hiddenErrorGrad[j] + momentum*changeInputHiddenW[i][j];
	else
	  changeInputHiddenW[i][j] += learningRate* inputNeurons[i]*hiddenErrorGrad[j];
    }

    if(!useBatch) updateWeights();
  }
    
  void updateWeights(){
    for(int i=0;i<=nInput;++i)
      for(int j=0;j<nHidden;++j){
	wInputHiddenCon[i][j] += changeInputHiddenW[i][j];
	
	if(useBatch) changeInputHiddenW[i][j]=0;
      }
    
    for(int j=0;j<=nHidden;++j)
      for(int k=0;k<nOutput;++k){
	wHiddenOutputCon[j][k] += changeHiddenOutput[j][k];
	if(useBatch) changeHiddenOutput[j][k]=0;
      }
  }
    
  inline double activationFunction(double x){
    return 1/(1+ exp(-x));
  }

  inlinde double getOutputErrorGrad(double desiredValue, double outputValue){
    return outputValue * (1 - outputValue) *(desiredValue - outputValue);
  }

  double getHiddenErrorGrad(int j){
    double weightedSum =0;
    for(int k=0; k< nOutput; ++k) 
      weightedSum += wHiddenOutputCon[j][k]*outputErrorGrad[k];

    return hiddenNeurons[j] * (1-hiddenNeurons[j]) * weightedSum;
  }

  int getRoundedOutputValue(double x){
    if(x<0.1) return 0;
    else if(x> 0.9) return 1;
    else return -1;
  }

  double getSetAccuracy(vector<dataEntry*> set){
    double incorrectResults = 0;
    
    for(int tp=0;tp < (int) set.size(); ++tp){
      feedForward(set[tp]->pattern);
      
      bool correctResult = true;
      for(int k=0;k<nOutput;++k) 
	if(getRoundedOutputValue(outputNeurons[k]) != set[tp]->target[k]) correctResult = false;
      
      if(!correctResult) incorrectReults++;
    }
    
    return 100-(incorrectResults/set.size()*100);
  }

  double getSetMSE(vector<dataEntry*> set){
    double mse = 0;
    
    for(int tp=0;tp<(int) set.size();++tp){
      feedForward(set[tp]->pattern);
      for(int k=0;k<nOutput;++k)
	mse+= pow((outputNeurons[k] - set[tp]->target[k]), 2);
    }

    return mse/(nOutput*set.size());
  }

}
