// add your imports here
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

vector<int> randTable =
{72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

struct node {
  bool h: 1;
  bool v: 1;
  bool visited: 1;
};

struct point2D {
  int x, y;
};

enum class Direction {
  Up = 0,
  Right = 1,
  Down = 2,
  Left = 3,
};

vector<vector<node>> board;
vector<bool> horizontals;
vector<bool> verticals;

//set up walls

void setUp(){};
void setDown(){};
void setLeft(){};
void setRight(){};

void getUp(){};
void getDown(){};
void getLeft(){};
void getRight(){};

void genMap (point2D limits)
{

}

int getRand (vector<int> randTable) {
  return 0;
}

void printMaze()
{

}

void BreakWall(point2D p, Direction d)
{
  switch (d) {
    case Direction::Up:

  }
}

vector<point2D> getVisitables(point2D p){
  if ()
}

int main(){
    int horizontals, verticals, steps = 0;

cin >> horizontals >> verticals >> steps;

}