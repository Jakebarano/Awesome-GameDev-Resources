#ifndef CAT_h
#define CAT_h
#include "IAgent.h"
#include "functions.h"


struct Cat : public IAgent {
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override {
    Board board(world, sideSize, catPos);

    vector<Point2D> path = buildPath(board);

    if (!path.empty()) {
      return path[path.size() - 1].toPair();
    } else {
      auto pos = board.catPos;
      auto neighbors = board.NeighborsInsideBoundariesNotBlocked(pos);
      return neighbors[0].toPair();
    }
  }
};
#endif