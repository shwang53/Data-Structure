/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    //return NULL;

    /**
    * @todo Implement this function!
    */

   if (theTiles.empty() == true){
     return NULL;
   }

   map<Point<3>, int> theMap;
   vector<Point<3>> eachTiles;
   unsigned length  = theTiles.size();
   eachTiles.resize(length);


   for (size_t i = 0; i < length; i++) {
     eachTiles[i].set(0, theTiles[i].getAverageColor().l);
     eachTiles[i].set(1, theTiles[i].getAverageColor().u);
     eachTiles[i].set(2, theTiles[i].getAverageColor().v);
     theMap[eachTiles[i]] = i;
   }

   // unsigned i=0;
   //
   // while( i < length ){
   //   LUVAPixel p = theTiles[i].getAverageColor();
   //     // double arr [3] = { p.l / 360, p.u, p.v};
   //     // Point<3> temp(arr);
   //     // eachTiles.push_back(temp);
   //     // theMap[temp] = i;
   //    eachTiles[i].set(0, theTiles[i].getAverageColor().l);
   //    eachTiles[i].set(1, theTiles[i].getAverageColor().u);
   //    eachTiles[i].set(2, theTiles[i].getAverageColor().v);
   //    theMap[eachTiles[i]] = i;
   //    i++;
   // }

   KDTree<3> tree(eachTiles);
   int row = theSource.getRows();
   int col = theSource.getColumns();
   MosaicCanvas* canvas = new MosaicCanvas(row, col);

   for (int i = 0; i < row; i++) {
     for (int j = 0; j < col; j++) {
        LUVAPixel pixel = theSource.getRegionColor(i, j);

       Point<3> temp;
       temp.set(0, pixel.l);
       temp.set(1, pixel.u);
       temp.set(2, pixel.v);

       Point<3> check = tree.findNearestNeighbor(temp);
       int index = theMap[check];
       canvas->setTile(i, j, &theTiles[index]);
     }
   }
   return canvas;

}
