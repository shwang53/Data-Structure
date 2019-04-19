#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
//start here
#include "mp1.h"
#include <iostream>




void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2

    cs225::PNG in;
    cs225::PNG out;

    //get original image = in.readFromFIle
    //get image that will be modified = out.readFromFile
    in.readFromFile(inputFile);
    out.readFromFile(inputFile);

    //go over each pixel from top to bottom.
    for (unsigned x = 0; x < in.width(); x++) {
        for (unsigned y = 0; y < in.height(); y++){

        //access the pixel information of each location.
        HSLAPixel & in_pixel = in.getPixel(x, y);
        HSLAPixel & out_pixel = out.getPixel(in.width()-x-1, in.height()-y-1);
        //switch the h,s,l,a
        out_pixel.h = in_pixel.h;
        out_pixel.l = in_pixel.l;
        out_pixel.s = in_pixel.s;
        out_pixel.a = in_pixel.a;

        }
    }
    //writing the modified image to outputFile
    out.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {

  PNG png(width, height);
  //png.readFromFile("in.png");
  //png.resize(800,800);


for(unsigned i =0; i<800; i++ ){
  for (unsigned x = i; x < 800-i; x++) {
      for (unsigned y = i; y < 800-i; y++){
          HSLAPixel & pixel = png.getPixel(x, y);

            pixel.h = 211 - i;
            pixel.s = 1;
            pixel.l = 0.5;
            pixel.a = 1;


          // else if (x >= 266 && x < 532){
          //   pixel.h = 100;
          //   pixel.s = 1;
          //   pixel.l = 1;
          //   pixel.a = 1;
          //
          // }else{
          //   pixel.h = 11;
          //   pixel.s = 1;
          //   pixel.l = 0.7;
          //   pixel.a = 1;
          // }

      }
  }
}


  // TODO: Part 3
  return png;
}
