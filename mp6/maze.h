//
/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <cstdlib>
#include <algorithm>

#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

class SquareMaze{

private:


public:


    int width;
    int height;
    int size;
    vector<int> down;
    vector<int> right;

   SquareMaze();
   void makeMaze(int width, int height);
   bool canTravel(int x, int y, int dir) const;
   void setWall(int x, int y, int dir, bool exists);
   vector<int> solveMaze();
   cs225::PNG * drawMaze() const;
   cs225::PNG * drawMazeWithSolution();

    PNG * drawCreativeMaze();

};

#endif
