#pragma once

#include<vector>

namespace ds
{
  class KDNode
  {
    std::vector<double> _values;
    int _d;
    KDNode* above;
    KDNode* below;
    

  KDNode(std::vector<double> val, int d): _values(val),_d(d){};
    ~KDNode()
      {
	_values.clear();
      }
  };
}
