
#include "Image.h"
#include "StickerSheet.h"
#include <iostream>


using namespace std;


StickerSheet::StickerSheet(const Image & picture, unsigned max){

    base_ = picture;
    capacity_ = max;
    layer_ = 0;

  //  Final = new Image();

    sticker_ = new Image[capacity_];
    xPos_ = new unsigned[capacity_];
    yPos_ = new unsigned[capacity_];
    valid_ = new unsigned[capacity_]; // 0 : false, 1 : true

    for(unsigned i = 0; i < capacity_; i++){
        //reset to be 0 and NULL;
        //sticker_ = NULL;
        xPos_[i] = 0;
        yPos_[i] = 0;
        valid_[i] = 0;
    }
    //  cout << "LINE : 28" <<endl;
}

void StickerSheet::copy(StickerSheet const & other){
//  cout << "LINE : 31" <<endl;
  //copy helper function.
    clear();
    base_ = other.base_;
    capacity_ = other.capacity_;
    layer_ = other. layer_;

    sticker_ = new Image[capacity_];
    xPos_ = new unsigned[capacity_];
    yPos_ = new unsigned[capacity_];
    valid_ = new unsigned[capacity_]; // 0 : false, 1 : true
  //  Final = new Image();

    for(unsigned i = 0; i < capacity_; i++){
        //deep copy
        sticker_[i] = other.sticker_[i];
        xPos_[i] = other.xPos_[i];
        yPos_[i] = other.yPos_[i];
        valid_[i] = other.valid_[i];
    }
    //  cout << "LINE : 51" <<endl;
}

void StickerSheet::clear(){
  //cout << "LINE : 31" <<endl;
  //clear or destroy helper function.
  if(sticker_ != NULL){
    delete[] sticker_; sticker_=NULL;
  }
  if(xPos_ != NULL){
    delete[] xPos_; xPos_ = NULL;
  }
  if(yPos_ != NULL){
    delete[] yPos_; yPos_ = NULL;

  }
  if(valid_ != NULL){
    delete[] valid_; valid_ = NULL;

  }
  // if(Final != NULL){
  //   delete Final; Final = NULL;
  //
  // }
    //cout << "LINE : 60" <<endl;

}

StickerSheet::~StickerSheet(){

    clear();
      //cout << "LINE : 66" <<endl;
}

StickerSheet::StickerSheet(const StickerSheet & other){
      sticker_ = NULL;
      xPos_ = NULL;
      yPos_ = NULL;
      valid_ = NULL;
     clear();
    copy(other);
      //cout << "LINE : 71" <<endl;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
    //cout << "LINE : 75" <<endl;
    if(this != &other){
        clear();
        copy(other);
    }
    return *this;
    //  cout << "LINE : 81" <<endl;
}


void StickerSheet::changeMaxStickers(unsigned max){

  //cout << "LINE : 106" <<endl;
    Image * temp_s = new Image[max];
    //temp_s = sticker_;

    unsigned * temp_v = new unsigned[max];
    //temp_v = valid_;

    unsigned * temp_x = new unsigned[max];
    //temp_x = xPos_;
    unsigned * temp_y = new unsigned[max];
    //temp_y = yPos_;
    //  cout << "LINE : 117" <<endl;

if(capacity_ >= max){
  for(unsigned i =0; i< max; i++){
      temp_s[i] = sticker_[i];
      temp_v[i] = valid_[i];
      temp_x[i] = xPos_[i];
      temp_y[i] = yPos_[i];
  }

}else if(capacity_ < max ){
  for(unsigned i =0; i< capacity_; i++){
      temp_s[i] = sticker_[i];
      temp_v[i] = valid_[i];
      temp_x[i] = xPos_[i];
      temp_y[i] = yPos_[i];
  }
  for(unsigned i = capacity_; i< max; i++){
    //  temp_s[i] = sticker_[i];
      temp_v[i] = 0;
      temp_x[i] = 0;
      temp_y[i] = 0;
  }


}


  //cout << "LINE : 125" <<endl;
    delete[] sticker_; sticker_=NULL;
    delete[] xPos_; xPos_ = NULL;
    delete[] yPos_; yPos_ = NULL;
    delete[] valid_; valid_ = NULL;


  //cout << "LINE : 132" <<endl;
    capacity_ = max;
  //  Image* sticker_ = new Image[capacity_];
  //  unsigned * valid_ = new unsigned[capacity_];
  //  unsigned * xPos_ = new unsigned[capacity_];
  //  unsigned * yPos_ = new unsigned[capacity_];

    // for(unsigned i=0; i<capacity_; i++){
    //   //  sticker_ = NULL;
    //     valid_[i] = 0;
    // }
//  for(unsigned i=0; i<capacity_; i++){
        sticker_ = temp_s;
        valid_ = temp_v;
        xPos_ = temp_x;
        yPos_ = temp_y;
//    }
//  cout << "LINE : 149" <<endl;
  // delete[] temp_s; temp_s = NULL;
   //delete[] temp_v; temp_v = NULL;
   //delete[] temp_x; temp_x = NULL;
   //delete[] temp_y; temp_y = NULL;

//  cout << "LINE : 154" <<endl;

}


int StickerSheet::addSticker (Image & sticker, unsigned x, unsigned y){
    //cout << "LINE : 162" <<endl;
  if(layer_ < capacity_){
    for(unsigned i=0; i<capacity_; i++){
        if( valid_[i] == 0){
        //    cout << "LINE : 113" <<endl;
            sticker_[i] = sticker;
            //  cout << "LINE : 168" <<endl;
            xPos_[i] = x;
            yPos_[i] = y;
            valid_[i] = 1;
            layer_ = i;
      //        cout << "LINE : 118" <<endl;
            break;
        }
    }
    //  cout << "LINE : 177" <<endl;
    return layer_;
  }else{
  //    cout << "LINE : 180" <<endl;
    return -1;
  }

}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if( valid_[index] == 0){
        return false;
    }else{
        xPos_[index] = x;
        yPos_[index] = y;
        return true;
    }
}


void StickerSheet::removeSticker(unsigned index){
  //  sticker_[index] = NULL;
  if(index < capacity_){
    //sticker_[index]= ;
    xPos_[index] = 0;
    yPos_[index] = 0;
    valid_[index] = 0;
  }

}

Image* StickerSheet::getSticker (unsigned index) const{
    if( valid_[index] == 1 ){
        return sticker_;
    }else{
      return NULL;
    }
}

Image StickerSheet::render() const{


//    cout << "LINE : 214" <<endl;
  unsigned WIDTH_ = 0;
  unsigned HEIGHT_ = 0;
  bool check = false;
  Image * Final = new Image(base_);

  for(unsigned i = 0; i<= layer_; i++){
    if(valid_[i] == 1){
       WIDTH_ = (base_.width() > (xPos_[i] + sticker_[i].width()) ?
                         base_.width() : (xPos_[i] + sticker_[i].width()));
       HEIGHT_ = (base_.height() > (yPos_[i] + sticker_[i].height()) ?
                          base_.height() : (yPos_[i] + sticker_[i].height()));
      check = true;
    }
  }
//    cout << "LINE : 226" <<endl;
  if(check){
    Final->resize(WIDTH_,HEIGHT_);
  for(unsigned i = 0; i<= layer_; i++){
    if(valid_[i] == 1){
        for(unsigned sticker_w = xPos_[i]; sticker_w < xPos_[i]+ sticker_[i].width(); sticker_w++){
          for(unsigned sticker_h = yPos_[i]; sticker_h < yPos_[i]+sticker_[i].height(); sticker_h++){
              if(sticker_[i].getPixel(sticker_w - xPos_[i], sticker_h - yPos_[i]).a != 0){
                  HSLAPixel & basePixel = Final->getPixel(sticker_w,sticker_h);
                  HSLAPixel & stickerPixel = sticker_[i].getPixel(sticker_w-xPos_[i],sticker_h-yPos_[i]);
                  basePixel.h = stickerPixel.h;
                  basePixel.s = stickerPixel.s;
                  basePixel.l = stickerPixel.l;
                  basePixel.a = stickerPixel.a;
              }
          }
        }
    }
  }
}
  //cout << "LINE : 247" <<endl;
  Image realFinal;
  realFinal = *Final;
    //cout << "LINE : 247" <<endl;
  delete Final; Final = NULL;
  return realFinal;
}
