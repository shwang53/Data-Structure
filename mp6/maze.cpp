
/* Your code here! */
#include "maze.h"

using namespace std;

//create the empty constructor
SquareMaze::SquareMaze() {

}
/*
Makes a new SquareMaze of the given height and width.

If this object already represents a maze it will clear all the existing data before doing so. You will start with a square grid (like graph paper) with the specified height and width. You will select random walls to delete without creating a cycle, until there are no more walls that could be deleted without creating a cycle. Do not delete walls on the perimeter of the grid.

Hints: You only need to store 2 bits per square: the "down" and "right" walls. The finished maze is always a tree of corridors.)

Parameters
width	The width of the SquareMaze (number of cells)
height	The height of the SquareMaze (number of cells
  */

//make maze with (int width, int height)
void SquareMaze::makeMaze(int width, int height) {

  this->width = width;
  this->height = height;
  size = width * height;

//initialize to be true at first.
  for (int i = 0; i < size; i++) {
    right.push_back(1);
    down.push_back(1);
  }

//create disjointset
  DisjointSets djs = DisjointSets();
  djs.addelements(size);


//until no wall, it will be deleted.
  int count = 0;
  while (count + 1 < size ) {
    //randomized x,y
    int rX = rand() % width;
    int rY = rand() % height;
    int rZ = rY * width;

    int dir = rand() % 2;

    int idx = rX + rZ;
    int temp = djs.find(idx);


    if (dir == 0) {
      if(rY + 1 < height && down[idx]){
        if(temp == djs.find(rX + (rY + 1) * width)){
          continue;
        }
        else {
            down[idx] = 0;
            djs.setunion(temp, djs.find(rX + (1 + rY) * width));
            count++;
          }
      }

    }
    else {
      if(rX + 1 < width  && right[idx] ){
        if (temp == djs.find(idx + 1)){
          continue;
        }
        else{
            right[idx] = 0;
            djs.setunion(temp, djs.find(idx + 1));
            count++;
          }
      }
    }
  }

}
/*
This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).

For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).

dir = 0 represents a rightward step (+1 to the x coordinate)
dir = 1 represents a downward step (+1 to the y coordinate)
dir = 2 represents a leftward step (-1 to the x coordinate)
dir = 3 represents an upward step (-1 to the y coordinate)
You can not step off of the maze or through a wall.

This function will be very helpful in solving the maze. It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution. So make sure that this function works!

Parameters
x	The x coordinate of the current cell
y	The y coordinate of the current cell
dir	The desired direction to move from the current cell
Returns
whether you can travel in the specified direction
*/

  bool SquareMaze::canTravel(int x, int y, int dir) const {

      int temp = y * width + x;

      switch(dir){
        case 0: if(right[temp])return false ; //right
                else return true;

        case 1: if(down[temp])return false ; //down
                else return true;

        case 2: if (x == 0) return false; //left
                else return !(right[temp -1]);

        case 3: if (y == 0) return false; // up
                else return !(down[x + (y - 1) * width]);
      }

      return false;
    }

  /*
    Sets whether or not the specified wall exists.

This function should be fast (constant time). You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. Our tests will call setWall to copy a specific maze into your implementation.

Parameters
x	The x coordinate of the current cell
y	The y coordinate of the current cell
dir	Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). You only need to support setting the bottom and right walls of every square in the grid.
exists	true if setting the wall to exist, false otherwise

    */

    void SquareMaze::setWall(int x, int y, int dir, bool exists) {
      // if (x < 0 || x >= width || y < 0 || y >= height ) return;
      if (dir == 1) {
        down[y * width + x] = exists; //down

      } else if (dir == 0) {
        right[y * width + x] = exists; //right
      }
    }

/*
Solves this SquareMaze.

For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.

Select the square in the bottom row with the largest distance from the origin as the destination of the maze. solveMaze() returns the winning path from the origin to the destination as a vector of integers, where each integer represents the direction of a step, using the same encoding as in canTravel().

If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.

Hint: this function should run in time linear in the number of cells in the maze.

Returns
a vector of directions taken to solve the maze
*/

  vector<int> SquareMaze::solveMaze() {
      //index starts
      queue<int> q;
      q.push(0);
      vector<int> optimalPath;

      map<int, int> mappa;

      mappa.insert(pair<int,int>(0, 0));

      map<int, int> backtrack;

      unsigned max = 0;
      int bd = 0;
      int count = 0;

        while (!q.empty()){
            int temp = q.front();
            q.pop();
            int x = temp % width;
            int y = temp / width;

            for (int dir = 0; dir < 4; dir++){
            	  int tempo;
                switch(dir){
                  case 0: tempo = (y * width) + (x+1);
                          if(canTravel(x, y, dir) && mappa.find(y*width+x+1) == mappa.end()){
                            q.push(tempo);
                            backtrack.insert(pair<int, int>(y*width+x+1, temp));
                              mappa.insert(pair<int, int>(tempo, mappa[temp]+1));
                          }
                          break; //right

                  case 1: tempo = ((y+1) * width) + x;
                            if(canTravel(x, y, dir) && mappa.find((y+1)*width+x) == mappa.end()){
                              q.push(tempo);
                              backtrack[tempo] = temp;
                                  mappa.insert(pair<int, int>(tempo, mappa[temp]+1));
                            }
                          break; //down

                  case 2: tempo = (y * width) + (x-1);
                          if(canTravel(x, y, dir) && mappa.find(y*width+x-1) == mappa.end()){
                            q.push(tempo);
                            backtrack[tempo] = temp;
                              mappa.insert(pair<int, int>(tempo, mappa[temp]+1));
                          }

                          break; //left
                  case 3: tempo = ((y-1) * width) + x;
                          if(canTravel(x, y, dir) && mappa.find((y-1)*width+x) == mappa.end()){
                            q.push(tempo);
                            backtrack[tempo] = temp;
                                mappa.insert(pair<int, int>(tempo, mappa[temp]+1));
                          }
                          break; //up
                }
            }

      	}


      	for(int x = 0; x < width ; x++){

        		int dest = ( (height-1) * width) + x;
        		vector<int> path;


        		while(dest != 0){

              //right
        			if(dest == backtrack[dest] + 1){
        				path.push_back(0);
        			}

              //left
        			if(dest == backtrack[dest] -1){
        				path.push_back(2);
        			}

              //down
        			if(dest == width + backtrack[dest]){
        				path.push_back(1);
        			}
              //
              //up
        			if(dest == backtrack[dest]-width){
        				path.push_back(3);
        			}

        			dest = backtrack[dest];
        		}

        		if(max < path.size()){
        			max = path.size();
        			optimalPath = path;
        			bd = dest;
        		}
      	}

        //Reverse the path
        reverse(optimalPath.begin(), optimalPath.end());
        return optimalPath;
}

/*
Draws the maze without the solution.

First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where height and width were the arguments to makeMaze. Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). For each square in the maze, call its maze coordinates (x,y). If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.

The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.

Returns
a PNG of the unsolved SquareMaze

*/



    PNG * SquareMaze::drawMaze() const {

      PNG* raw = new PNG(width*10 + 1, height*10 + 1);

      for (int i = 0; i < height*10 + 1; i++) {
        HSLAPixel& p = raw->getPixel(0, i);
        p.l = 0;
      }

      for (int i = 10; i < width*10 + 1; i++) {
        HSLAPixel& p = raw->getPixel(i, 0);
        p.l = 0;
      }

      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {


          if (right[y * width + x]) {
            for (int i = 0; i <= 10; i++) {
              HSLAPixel& p = raw->getPixel(10 * x + 10, 10 * y + i);
              p.l = 0;
            }
          }


          if (down[y * width + x]) {
            for (int i = 0; i <= 10; i++) {
              HSLAPixel& p = raw->getPixel(10 * x + i, 10 * y + 10);
              p.l = 0;
            }
          }


        }
      }
      return raw;
    }
/*
    This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

    Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the second step is right, color pixels (5,15) through (15,15) red. Then if the third step is up, color pixels (15,15) through (15,5) red. Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.

    Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.

    Returns
    a PNG of the solved SquareMaze

    */

    PNG * SquareMaze::drawMazeWithSolution() {

      PNG * final = drawMaze();

    	vector<int> optimalPath;
      optimalPath = solveMaze();

    	int x = 5 , y = 5;

    	for (int dir : optimalPath){
          for (int k = 1; k <= 10; k++){//color 11 pixels in a line

      			HSLAPixel& p = final->getPixel(x,y);
      			p.h = 0;
      			p.s = 1;
      			p.l = 0.5;
      			p.a = 1;

            switch(dir){
              case 0: x++; break;
              case 1: y++; break;
              case 2: x--; break;
              case 3: y--; break;
            }

    		  }

      		HSLAPixel& p = final->getPixel(x,y);
      		p.h = 0;
      		p.s = 1;
      		p.l = 0.5;
      		p.a = 1;

    	}

  	for(int i =1; i < 10; i++){
  		HSLAPixel& p = final->getPixel(x-5+i, y+5);
  		p.l = 1;

  	}

    return final;

}

PNG * SquareMaze::drawCreativeMaze()  {
  // right[0] = 1;
  // down[1] = 2;
  // right [2] =3 ;

  PNG* raw = new PNG(width*10 + 1, height*10 + 1);

  // int small = height < width ? height :width;
  //


    for (int i = 0; i < height*10 + 1; i++) {
      HSLAPixel& p = raw->getPixel(0, i);
      p.h = 255;
      p.s = 1;
      p.l = 0.7;
    }



    for (int i = 10; i < width*10 + 1; i++) {
      HSLAPixel& p = raw->getPixel(i, 0);
      p.l = 0.7;
      p.h = width*height % 360;
      p.s = 1;
    }





  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {


      if (right[y * width + x]) {
        for (int i = 0; i <= 10; i++) {
          HSLAPixel& p = raw->getPixel(10 * x + 10, 10 * y + i);
          p.h = 25;
          p.s = 1;
          p.l = 0.5;
        }
      }


      if (down[y * width + x]) {
        for (int i = 0; i <= 10; i++) {
          HSLAPixel& p = raw->getPixel(10 * x + i, 10 * y + 10);
          p.h = 255;
          p.s = 1;
          p.l = 0.5;
        }
      }


    }
  }

  for (int i = 0; i < height + 1; i++) {
    HSLAPixel& p = raw->getPixel(0, i);
    p.h = 100;
    p.s = 1;
    p.l = 0.8;
  }


  return raw;
}
