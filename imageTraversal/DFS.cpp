
#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
 {
  /** @todo [Part 1] */
  start_= start;
  png_ = (png);
  tolerance_ = (tolerance);

  s.push(start_);

  occupied.resize(png.width(),vector<bool>(png_.height()));

  for(unsigned int i = 0; i < png_.width(); i++)
    for(unsigned int j = 0; j < png_.height(); j++){
      occupied[i][j] = false;
    }
}



/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  // DFS * temp = new DFS(png_, start_, tolerance_);
  // return ImageTraversal::Iterator(*temp,start_);
  ImageTraversal * traversal = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */


  HSLAPixel & comparePixel = png_.getPixel(start_.x,start_.y);


  if (point.x < png_.width() -1)
    {
      if(calculateDelta(png_.getPixel(point.x + 1,point.y),comparePixel) <=tolerance_  && !occupied[point.x+1][point.y]){
        Point east(point.x+1,point.y);
        s.push(east);
      //  occupied[point.x+1][point.y] = true;

      }
    }

  if (point.y  < png_.height() -1 ) {

      if(calculateDelta(png_.getPixel(point.x,point.y + 1),comparePixel) <=tolerance_ && !occupied[point.x][point.y+1]){
        Point south(point.x,point.y + 1);
        s.push(south);
        //occupied[point.x][point.y + 1] = true;
      }
  }
  if ((int)point.x  >= 1 ) {

      if(calculateDelta(png_.getPixel(point.x -1,point.y),comparePixel) <=tolerance_&&  !occupied[point.x - 1][point.y]){
        Point west(point.x-1,point.y);
        s.push(west);
        //occupied[point.x-1][point.y] = true;
      }
  }
  if ((int)point.y  >= 1 ) {

      if(calculateDelta(png_.getPixel(point.x ,point.y - 1),comparePixel) <=tolerance_&&  !occupied[point.x][point.y - 1]){
        Point north(point.x,point.y - 1);
        s.push(north);
        //occupied[point.x][point.y - 1] = true;
      }
  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
    Point temp = s.top();
    if(empty()) {return Point(0,0);}
    else{
      while(occupied[temp.x][temp.y]){
        s.pop();
      }
    }
    occupied[temp.x][temp.y] = true;
    s.pop();
    return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() {
  /** @todo [Part 1] */
  Point temp = s.top();
  while((!empty()) && occupied[temp.x][temp.y]) {
      s.pop();
  }
  if(empty()){return Point(0,0);}
  else{return temp;}
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return s.empty();
}
