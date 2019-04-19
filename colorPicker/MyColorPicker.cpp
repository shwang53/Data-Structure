#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
 MyColorPicker::MyColorPicker(double temp) {
      h = 1;
      s = 1;
      l = temp;
  };

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel (h,s,0.8);

  // if(x<100)
  //   pixel = HSLAPixel(1, 0.5, 1);
  // else if(x>=100 && x<200)
  //   pixel = HSLAPixel(1, 1, 0.5);
  // else
  //   pixel =HSLAPixel(0.5, 1, 1);


  return pixel;

}
