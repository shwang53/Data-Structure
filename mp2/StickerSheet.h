/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <iostream>

class StickerSheet{
public:
    StickerSheet(const Image & picture, unsigned max);
      /*
      Initializes this StickerSheet with a base picture and the ability
      to hold a max number of stickers (Images) with indices 0 through max - 1.

      Parameters
      picture	The base picture to use in the StickerSheet
      max	The maximum number of stickers (Images) on this StickerSheet

      */

      //helper function make life easier : cpy, destroy.
      ~StickerSheet();
      StickerSheet(const StickerSheet & other);
      const StickerSheet & operator=(const StickerSheet &other);

      //helper function
      void copy(StickerSheet const & other);
      void clear();


      void changeMaxStickers(unsigned max);
      int addSticker (Image & sticker, unsigned x, unsigned y);
      bool translate(unsigned indext, unsigned x, unsigned y);
      void removeSticker(unsigned index);
      Image* getSticker (unsigned index) const;
      Image render() const;



  private:

    Image base_;
    unsigned capacity_;
    unsigned layer_;

    Image* sticker_;
    unsigned* xPos_;
    unsigned* yPos_;
    unsigned* valid_;
  //  Image * Final;




};
