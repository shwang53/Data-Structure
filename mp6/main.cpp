#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
  //  cout << "Add your own tests here! Modify main.cpp" << endl;
   SquareMaze maze;
   maze.makeMaze(400,500);



  	PNG * output = maze.drawCreativeMaze();
  	output->writeToFile("creative"+ string(".png"));
    return 0;
}
