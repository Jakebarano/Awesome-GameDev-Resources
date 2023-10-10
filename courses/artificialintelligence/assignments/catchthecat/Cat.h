#ifndef CAT_h
#define CAT_h
#include "IAgent.h"

struct Cat : public IAgent {
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

    return {0,0}; // todo: change this
  }

  int GetNeighbors(const std::vector<bool>& world, std::pair<int,int> point, int sideSize ) {

    std::pair<int,int> NorthWest = {0, 0};
    std::pair<int,int> sideOne =  {0, 0};
    std::pair<int,int> sideTwo =  {0, 0};
    std::pair<int,int> sideThree =  {0, 0};
    std::pair<int,int> sideFour =  {0, 0};
    std::pair<int,int> sideFive =  {0, 0};

    if (point.second % 2 == 0) {
      NorthWest = {point.first, point.second - 1};  //Rename for
      sideOne = {point.first , point.second - 1};
      sideTwo = {point.first + 1, point.second};
      sideThree = {point.first, point.second + 1};
      sideFour = {point.first - 1, point.second + 1};
      sideFive = {point.first - 1, point.second};
    }
    else
    {
      NorthWest = {point.first, point.second - 1};
      sideOne = {point.first + 1, point.second - 1};
      sideTwo = {point.first + 1, point.second};
      sideThree = {point.first + 1, point.second + 1};
      sideFour = {point.first, point.second + 1};
      sideFive = {point.first - 1, point.second};
    }

    auto index = point.second * sideSize + point.first;
    auto sideSquared = sideSize * sideSize;
    if (index >= sideSquared) index %= sideSquared;
    return world[currentBufferId % 2][index];

    return world.Get(NorthWest) + world.Get(sideOne) + world.Get(sideTwo) + world.Get(sideThree) + world.Get(sideFour) + world.Get(sideFive);
  }
};
#endif