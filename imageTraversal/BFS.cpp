#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
  {
  /** @todo [Part 1] */
  start_= start;
  png_ = (png);
  tolerance_ = (tolerance);

  q.push(start);


  occupied.resize(png.width(),vector<bool>(png_.height()));
  for(unsigned int i = 0; i < png_.width(); i++)
    for(unsigned int j = 0; j < png_.height(); j++){
      occupied[i][j] = false;
    }
    occupied[start_.x][start_.y] = true;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  // BFS * temp = new BFS(png_, start_, tolerance_);
  // return ImageTraversal::Iterator(*temp,start_);
  ImageTraversal * traversal = new BFS(png_, start_, tolerance_);
 return ImageTraversal::Iterator(traversal);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */

  HSLAPixel & comparePixel = png_.getPixel(start_.x,start_.y);


  if (point.x < png_.width() -1)
    {
      if(calculateDelta(png_.getPixel(point.x + 1,point.y),comparePixel) <=tolerance_  && !occupied[point.x+1][point.y]){
        Point east(point.x+1,point.y);
        q.push(east);
        occupied[point.x+1][point.y] = true;

      }
    }

  if (point.y  < png_.height() -1 ) {

      if(calculateDelta(png_.getPixel(point.x,point.y + 1),comparePixel) <=tolerance_ && !occupied[point.x][point.y+1]){
        Point south(point.x,point.y + 1);
        q.push(south);
        occupied[point.x][point.y + 1] = true;
      }
  }
  if (point.x < png_.width() -1 && (int)point.x  >= 1 ) {

      if(calculateDelta(png_.getPixel(point.x -1,point.y),comparePixel) <=tolerance_&&  !occupied[point.x - 1][point.y]){
        Point west(point.x-1,point.y);
        q.push(west);
        occupied[point.x-1][point.y] = true;
      }
  }
  if (point.y  < png_.height() -1 && (int)point.y  >= 1 ) {

      if(calculateDelta(png_.getPixel(point.x ,point.y - 1),comparePixel) <=tolerance_&&  !occupied[point.x][point.y - 1]){
        Point north(point.x,point.y - 1);
        q.push(north);
        occupied[point.x][point.y - 1] = true;
      }
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point temp = q.front();
  q.pop();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() {
  /** @todo [Part 1] */

  return q.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return q.empty();
}
