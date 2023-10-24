#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <cstdint>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

//
float sideSize = 9;

struct Point2D {
  int32_t x, y;
  Point2D() : x(0), y(0) {}  // DEFAULT CONSTRUCTOR
  Point2D(int32_t x, int32_t y) : x(x), y(y) {}
  // for unordered_set unordered_map
  uint64_t hash() const noexcept { return ((uint64_t)x) << 32 | (uint64_t)y; }
  // for priority_queue, map, set
  bool operator<(const Point2D& p) const { return x < p.x || (x == p.x && y < p.y); }
  // converts pair<int, int> to Point2D
  Point2D(const pair<int32_t, int32_t>& p) : x(p.first), y(p.second) {}
  // converts Point2D to pair<int, int>
  // add other operators, acessors, etc. ex.: NE(), NW(), SE(), SW(), E(), W()  //DONE

  Point2D& operator=(const pair<int32_t, int32_t>& p){
    x = p.first;
    y = p.second;
    return *this;
  }

  bool operator==(const Point2D& p) const
  {
        return x == p.x && y == p.y;
  }

  bool operator!=(const Point2D& p) const
  {
      return x != p.x || y != p.y;
  }
  inline Point2D NW() const
  {
      return (y % 2 == 0) ? Point2D(x-1, y-1) : Point2D(x, y-1);
  }
  inline Point2D NE() const
  {
      return (y % 2 == 0) ? Point2D(x, y-1) : Point2D(x+1, y-1);
  }
  inline Point2D E() const
  {
      return {x+1, y};
  }
  inline Point2D W() const
  {
      return {x-1, y};
  }
  inline Point2D SW() const
  {
      return (y % 2 == 0) ? Point2D(x-1, y+1) : Point2D(x, y+1);
  }
  inline Point2D SE() const
  {
      return (y % 2 == 0) ? Point2D(x, y+1) : Point2D(x+1, y+1);
  }

  inline bool IsInsideBoardBoundaries(int32_t sideSize) const {
      return abs(x) <= sideSize/2 && abs(y) <= sideSize/2;
  }

  inline vector<Point2D> Neighbors() const
  {
      return vector<Point2D> {NW(), NE(), E(), W(), SW(), SE()};
  }

  std::pair<int, int> toPair() { return {x, y}; }

};

// tell the compiler that we want to use Point2D as a key in unordered_set and unordered_map
template <> struct std::hash<Point2D> {
  std::size_t operator()(const Point2D& p) const noexcept { return p.hash(); }
};
struct AStarNode {
  Point2D pos;
  float accumulatedCost;
  float heuristic;
  // for priority_queue
  bool operator < (const AStarNode& n) const{
    return this->accumulatedCost + this->heuristic < n.accumulatedCost + n.heuristic;
  }
};



// Build Path Algorithm for A*
vector<Point2D> buildPath(Board& board){
  vector<Point2D> path; // to be built and returned
  priority_queue<AStarNode> frontier; // the elements that will be explored
  unordered_map<Point2D, Point2D> cameFrom; // the flow field. if have the key, it means it is visited

  const auto& cat = board.catPos; // cat
  Point2D exitIt = cat; // the exit position when we found it
  frontier.push({cat, 0, board.distanceToBorder(cat)}); // bootstrap
  cameFrom[cat]=cat; // bootstrap
  while (frontier.size() > 0) { // while we can consume
    auto current = frontier.top(); // get the next element to consume
    frontier.pop(); // consume
    if(board.CatWinAtPosition(current.pos)){ // stop condition
      exitIt = current.pos; // store the exit position
      break; // quit early
    }
    auto candidates = board.NeighborsInsideBoundariesNotBlocked(current.pos); // vicinity
    for (const auto& neighbor : candidates) { // iterate over the candidates
      if (neighbor != cat && !cameFrom.contains(neighbor)) { // if not visited and not the cat
        frontier.push({neighbor, current.accumulatedCost + 1, board.distanceToBorder(neighbor)}); // produce
        cameFrom[neighbor] = current.pos; // update flow field
      }
    }
  }
  while (exitIt != cat) { // build the path. using Exit as iterator
    path.push_back(exitIt); // add to the path
    exitIt = cameFrom[exitIt]; // update the iterator
  } // path.front() is the exit, path.back() is first possible cat move
  return path; // return the path
}

float distToBorder(Point2D p) {
  if (abs(p.y) > abs(p.x))
    return sideSize / 2 - abs(p.y);
  else
    return sideSize / 2 - abs(p.x);
}


////Unused stuffs to be removed?

//namespace std {
//  template <> struct hash<Point2D> {
//    std::size_t operator()(const Point2D& p) const noexcept { return p.hash(); }
//  };
//}
#endif  // AWESOMECPPCOURSE_FUNCTIONS_H
