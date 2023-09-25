#include <iostream>
#include <vector>

using namespace std;

vector<bool> currentstate;
vector<bool> oldstate;

int cols, rows, steps;

struct  Point{
  int x, y;
  Point Up(){return {x, (y - 1) < 0?rows - 1:y - 1};}
  Point Down(){ return { x, (y + 1) >=rows?0:y + 1};}
  Point Left(){ return {(x-1) < 0 ? cols-1: x, y};}
  Point Right(){ return {(x+1) >= cols? 0: x + 1, y};}
};

bool get(Point p) { return }

int main(){

  cin >> cols >> steps;


  currentstate.resize(rows * cols);
  oldstate.resize(rows * cols);

  for (int l = 0; l < rows; l++) {
    for (int c = 0; c < cols; c++) {
      char input;
      cin >> input;

      switch (input) {
        case '.':
        oldstate[rows * l + c] == false;
        currentstate[rows * l + c] == false;
        break;
      }
    }
  }
};