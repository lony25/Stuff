#pragma once

#include<random>
#include<vector>
#include<cmath>

#include "redBlackTree/redBlackTree.h"
#include "kdNode.h"

namespace ds
{
  class KDTree
  {
  private:
    int _nodeCount=0;
    KDNode* _root;
    int _dimensionCount = 0;
    std::random_device rd;
    
    //For first nearest neighbor
    std::vector<double> _nearestNeighbor{};
    double _minDist{0.0};

  public:
  KDTree():_root(){}
    ~KDTree
      {
	delete _root;
      }
    
    int getSize()
    {
      return _nodeCount;
    }
    
    void buildTree(std::vector<std::vector<double>> points)
    {
      if(points.size()==0)
	return;
      _dimensionCount = points.at(0).size();
      _root = generateNode(0,points,0,points.size()-1);
    }

    //method to get nearest neighbor
    std::vector<double> nearest(std::vector<double> targetPoint)
      {
	if(!_root)
	  return nullptr;
	
	findParent(targetPoint, _root, 0);
	nearest(_root, targetPoint);
	return _nearestNeighbor;
      }

  private:
    KDNode* generateNode(int currentD, std::vector<std::vector<double>> points, int left, int right)
    {
      
      if(right< left)
	return nullptr;
      
      _nodeCount++;
      
      if(right==left)
	return KDNode(points.at(left), currentD);

      int m = (right-left)/2;
      
      std::vector<double> medianNode = randomizedSelect(points, m, left, right, currentD);

      KDNode* node{medianNode, currentd};

      currentD++;

      if(currentD==_dimensionCount)
	currentD=0;
      
      node->below = generateNode(currentD, points, left, left+m-1);
      node->above = generateNode(currentD, points, left+m+1, right);
      return node;
    }

    std::vector<double> randomizedSelect(std::vector<std::vector<double>> points, int i, int left, int right, int currentD)
      {
	int p = left;
	int r = right;
	
	while(true)
	  {
	    if(p==r)
	      return points.at(p);
	    
	    int q = randomizedPartition(points, p, r, currentD);
	    int k = q-p+1;
	    if(i==k-1)
	      return points.at(q);
	    else if(i<k)
	      r = q-1;
	    else
	      {
		i = i-k;
		p = q+1;
	      }
	  }
      }

    int randomizedPartition(std::vector<std::vector<double>> points, int p, int r, int currentD)
    {
      int i=0;
      if(p<r)
	i = p+ (rd()%(r-p)+1);
      else
	i = r + (rd()%(p-r)+1);
      swap(points, r, i);
      return partition(points, p, r, currentD);
    }

    int partition(std::vector<std::vector<double>> points, int p, int r, int currentD)
    {
      std::vector<double> x = points.at(r);
      int i= p-1;
      for(int j=p; j<=r-1;++j)
	{
	  if(points.at(j).at(currentD) <= x.at(currentD))
	    {
	      i++;
	      swap(points, i, j);
	    }
	}
      swap(points, i+1, r);
      return i+1;
    }

    void swap(std::vector<std::vector<double>> points, int i, int j)
    {
      std::vector<double> valueI{points.at(i)};
      points.at(i) = points.at(j);
      points.at(j) = valueI;
    }

    //where point is to be inserted in KDD tree
    void findParent(std::vector<double> target, KDNode* node, int d)
    {
      if(target.at(d) < node->_values.at(d))
	{
	  if(++d == _dimensionCount)
	    d=0;
	  if(node->below == nullptr)
	    {
	      _nearestNeighbor = node->_values;
	      _minDist = distance(node->_values, target);
	      return;
	    }
	  
	  findParent(target, node->below, d);
	}
      
      if(++d == _dimensionCount)
	d=0;
      
      if(node->above==nullptr)
	{
	  nearestNeighbor = node->_values;
	  _minDist = distance(node->_values, target);
	  return;
	}
      findParent(target, node->above, d);
    }

    void nearest(KDNode* node, std::vector<double> targetPoint)
    {
      double d{distance(node->_values, targetPoint)};
      
      if(d<_minDist)
	{
	  _minDist = d;
	  _nearestNeighbor = node->values;
	}
      
      int dMinus = node->_d - 1;
      if(dMinus < 0)
	dMinus = _dimensionCount - 1;

      double perpendicularDistance = std::abs(node->_values.at(node->_d) - targetPoint.at(dMinus));
      if(perpendicularDistance < _minDist)
	{
	  if(node->above)
	    nearest(node->above, targetPoint);
	  if(node->below)
	    nearest(node->below, targetPoint);
	}
      else
	{
	  if(targetPoint.at(dMinus) < node->_values.at(node->_d))
	    {
	      if(node->below)
		nearest(node->below, targetPoint);
	    }
	  else if(node->above)
	    nearest(node->above, targetPoint);
	}
    }

    double distance(std::vector<double> node1, std::vector<double> node2)
    {
      double sum = 0;
      for(int i=0;i < node1.size(); ++i)
	sum += std::pow(node1.at(i) - node2.at(i), 2);
      
      return pow(sum, 0.5);
    }
    
  };
}
