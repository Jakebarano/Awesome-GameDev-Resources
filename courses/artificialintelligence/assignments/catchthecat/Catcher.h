#ifndef CATCHER_H
#define CATCHER_H

#include "IAgent.h"
#include "functions.h"

struct Catcher : public IAgent {
  pair<int, int> move(const std::vector<bool>& world, std::pair<int, int> catPos, int sideSize) override {
    Board board(world, sideSize, catPos);

    vector<Point2D> path = buildPath(board);

    if (!path.empty()) {
      return path[0].toPair();
    } else {
      auto pos = board.catPos;
      auto neighbors = board.NeighborsInsideBoundariesNotBlocked(pos);
      return neighbors[0].toPair();
    }
  }
};

#endif //CATCHER_H