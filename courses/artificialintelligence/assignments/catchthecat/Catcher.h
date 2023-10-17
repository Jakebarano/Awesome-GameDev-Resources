#ifndef CATCHER_H
#define CATCHER_H
#include "IAgent.h"
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>

struct Catcher : public IAgent {
  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{

    // source cat
    // destination exitPoint
    // camefrom, set of elements from frontier, queue frontier, visited;


    //TODO: Change ALL POINT2D to std::pair<int,int> (will be more efficient than making a Point2D struct.
    //TODO: FIX OTHER ISSUES

    unordered_map<Point2D, Point2D> cameFrom;
    unordered_set<Point2D> frontierSet;
    queue<Point2D> frontier;
    unordered_map<Point2D, bool> visited;
    Point2D current;

    //auto cPos = w->getCat();   //Not needed
    frontier.push(catPos);
    frontierSet.insert(catPos);
    Point2D exitPoint = Point2D(INT_MAX, INT_MAX);

    while (!frontier.empty() && exitPoint == Point2D(INT_MAX, INT_MAX))
    {
      current = frontier.front();
      frontier.pop();
      frontierSet.erase(current);
      visited[current] = true;

      //const vector<Point2D> neighbors = w->neighbors(current);  //gonna need a simple neighbors function

      for (auto next : neighbors) {
        if (!visited[next] && next != catPos && !w->getContent(next) && !frontierSet.contains(next))
        {
          frontier.push(next);
          frontierSet.insert(next);
          cameFrom[next] = current;

          if(w->catWinsOnSpace(next))
          {
            exitPoint = next;
            break;
          }
        }
      }
    }

    if (exitPoint == Point2D(INT_MAX, INT_MAX)) {
      return {};  // Return an empty path
    }

    vector<Point2D> path;   //compile path form cameFrom and return it.

    current = exitPoint;

    while (current != catPos)
    {
      path.push_back(current);
      current = cameFrom[current];
    }
    //return path;  //Remove Later.
    //// Do Not Return Path, fix code below this to determine movement based off path after the while  and return it as a std::pair<int, int>.
      if (!path.empty())
      {
        return path[0];
      }
      else {

        auto pos = world->getCat();
        auto neighbors = world->neighbors(pos);
        std::unordered_set<Point2D> availableNeighbors (neighbors.begin(), neighbors.end());

        while(!availableNeighbors.empty())
        {
          for(auto next : neighbors)
          {
            if(world->getContent(next))
            {
              availableNeighbors.erase(next);
            }
          }

          auto rand = Random::Range(0, availableNeighbors.size()-1);

          for(auto it = availableNeighbors.begin(); it != availableNeighbors.end(); it++)
          {
            if (rand == 0)
            {
              return *it;
            }
            rand--;
          }
        }
      }
    }


    return {0,0}; // todo: change this
  }
};
#endif