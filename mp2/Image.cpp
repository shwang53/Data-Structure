
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

namespace cs225{
    void Image::lighten(){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.l += 0.1;
          if(pixel.l > 1)
            pixel.l = 1;
        }
      }

    }
    void Image::lighten(double amount){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.l += amount;
          if(pixel.l > 1)
            pixel.l = 1;
        }
      }
    }

    void Image::darken(){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.l -= 0.1;
          if(pixel.l < 0)
            pixel.l = 0;
        }
      }
    }
    void Image::darken(double amount){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.l -= amount;
          if(pixel.l < 0)
            pixel.l = 0;
        }
      }
    }
    void Image::saturate(){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.s += 0.1;
          if(pixel.s > 1)
            pixel.s = 1;
        }
      }

    }
    void Image::saturate(double amount){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.s += amount;
          if(pixel.s > 1)
            pixel.s = 1;
        }
      }
    }
    void Image::desaturate(){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.s -= 0.1;
          if(pixel.s < 0)
            pixel.s = 0;
        }
      }

    }
    void Image::desaturate(double amount){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.s -= amount;
          if(pixel.s < 0)
            pixel.s = 0;
        }
      }
    }

    void Image::grayscale(){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.s =0;
      }
    }
  }

    void Image::rotateColor(double degrees){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          pixel.h += degrees;
          if(pixel.h > 360){
            pixel.h -= 360;
          }else if (pixel.h <0){
            pixel.h += 360;
          }
      }
    }
  }

    void Image::illinify(){
      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){
          HSLAPixel & pixel = this->getPixel(x,y);

          if(pixel.h > 113.5 && pixel.h <= 293.5){
            pixel.h = 216.0;
          }else{
            pixel.h =11.0;
          }
      }

    }
  }

void Image::scale(double factor){

/*
      PNG ori;
      unsigned this_width_ = ceil(width() * factor);
      unsigned this_height_ = ceil(height() * factor);

      this->resize(this_width_, this_height_);

      for(unsigned x =0; x<width(); x++){
        for(unsigned y=0; y<height(); y++){

          HSLAPixel & this_pixel_ = this->getPixel(x,y);
          HSLAPixel & ori_pixel_ = ori.getPixel(ceil(x/factor),ceil(y/factor));

          this_pixel_.h = ori_pixel_.h;
            this_pixel_.s = ori_pixel_.s;
              this_pixel_.l = ori_pixel_.l;
                this_pixel_.a = ori_pixel_.a;
        }
      }
  }
  */


  //declaring newly scaled plate of pixel.
	unsigned new_width_ = floor(this->width() * factor);
	unsigned new_height_ = floor(this->height() * factor);

  //creating HSLAPixel array as many as the whole new pixels.
	HSLAPixel * new_pixel_ = new HSLAPixel[new_width_ * new_height_];

	for (unsigned x = 0; x < new_width_ ; x ++){
		for (unsigned y = 0; y < new_height_ ; y++){
        // cf. nearest neighbor to fill up the empty pixel / shrink the pixels.
        // by dividing by factor = get new as many pixels as new one.
        //floor : prevent accessing over the fram or on the frame.
				HSLAPixel & old_pixel_ = this->getPixel(floor(x/factor),floor(y/factor));
				new_pixel_[ (x + (y * new_width_)) ]= old_pixel_;

			}
		}
    //resize the plate of pixels to the newly scaled.
		this->resize(new_width_,new_height_);

for (unsigned x = 0; x < new_width_ ; x ++){
		for (unsigned y = 0; y < new_height_ ; y++){
      //insert the pixels in the array to this.
			this->getPixel(x,y) = new_pixel_[ (x + (y * new_width_)) ];
		}
	}

}

  void Image::scale(unsigned w, unsigned h){
    //get each factor by given / original width
    double w_factor_ = ( w / width());
    double h_factor_ = ( h / height());
    //scale to the small factor so does not overflow.
    w_factor_ < h_factor_ ? scale(w_factor_) : scale(h_factor_);
  }
}
