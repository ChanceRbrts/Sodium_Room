#include "map.h"

Map::Map(int sID){
   x = 0;
   y = 0;
   w = 0;
   h = 0;
   prevCX = 0;
   prevCY = 0;
   superMapID = sID;
   firstLoad = true;
}

std::vector<Level *> Map::getUnloadedLevelsInArea(double X, double Y, double W, double H){
   std::vector<Level *> levs;
   // Change to level coordinates by removing gaps.
   double rX = translateMapCoord(X, true, true);
   double rY = translateMapCoord(Y, false, true);
   double rX2 = translateMapCoord(X+W, true, true);
   double rY2 = translateMapCoord(Y+H, false, true);
   for (int i = 0; i < levels.size(); i++){
      Level* l = levels[i];
      double lX = l->getMXOff();
      double lY = l->getMYOff();
      double lW = l->w;
      double lH = l->h;
      if (rX <= lX+lW && rX2 >= lX && rY <= lY+lH && rY2 >= lY){
         if (!l->getLoaded()){
            // Add gaps before moving the level into the world.
            double trueX = translateMapCoord(lX, true, false);
            double trueY = translateMapCoord(lY, false, false);
            l->moveRoom(trueX, trueY, false);
            // Now, see if a bisection needs to hapen.
            std::map<double, double>::iterator it = horizontalMapGap.begin();
            // Check for a horizontal bisection.
            for (; it != horizontalMapGap.end(); it++){
               if (it->first > lX+lW) break;
               if (it->first >= lX && it->first <= lX+lW){
                  // Translate the bisection to world coords.
                  l->startBisect(true, it->first-lX+trueX, it->second);
               }
            }
            it = verticalMapGap.begin();
            // Check for a vertical bisection.
            for (; it != verticalMapGap.end(); it++){
               if (it->first > lY+lH) break;
               if (it->first >= lY && it->first <= lY+lH){
                  // Translate the bisection to world coords.
                  l->startBisect(false, it->first-lY+trueY, it->second);
               }
            }
            levs.push_back(l);
         }
      }
   }
   return levs;  
}

void Map::addLevel(Level* l, double X, double Y){
   l->moveInMap(X*32, Y*32, false);
   l->moveRoom(X*32, Y*32, false);
   // pointInt area = (pointInt){(int)(X/100), (int)(Y/100), 0};
   if (levels.size() == 0){
      x = l->getMXOff();
      y = l->getMYOff();
      w = l->w;
      h = l->h;
   } else{
      float levX = l->getMXOff();
      float levY = l->getMYOff();
      float levW = l->w;
      float levH = l->h;
      // Modify the leftmost bounds first, since they could affect w and h.
      if (levX < x){
         float dX = x-levX;
         w += dX;
         x = levX;
      }
      if (levY < y){
         float dY = y-levY;
         h += dY;
         y = levY;
      }
      // Now, affect the rightmost bounds, since they can't affect x or y.
      if (levX+levW-x > w) w = levX+levW-x;
      if (levY+levH-y > h) h = levY+levH-y;
   }
   levels.push_back(l);
}

bool Map::inBounds(double X, double Y, double W, double H){
   double mX = x;
   double mY = y;
   double mX2 = x+w;
   double mY2 = y+h;
   // Adjust the bounds of the map according to the amount of gaps in the level.
   std::map<double, double>::iterator it = horizontalMapGap.begin();
   // Alter the horizontal bounds first.
   for (; it != horizontalMapGap.end(); it++){
      if (it->first <= x) mX += it->second;
      if (it->first <= x+w) mX2 += it->second;
      else break;
   }
   // Alter the vertical bounds.
   it = verticalMapGap.begin();
   for (; it != verticalMapGap.end(); it++){
      if (it->first <= y) mY += it->second;
      if (it->first <= y+w) mY2 += it->second;
      else break;
   }
   return mX <= X+W && mX2 >= X && mY <= Y+H && mY2 >= Y;
}

double Map::translateMapCoord(double prevCoord, bool horizontal, bool reverse){
   std::map<double, double> toUse = horizontal ? horizontalMapGap : verticalMapGap;
   std::map<double, double>::iterator it = toUse.begin();
   double coord = prevCoord;
   if (reverse){
      // Get rid of all of the gaps.
      double gapLength = 0;
      for (; it != toUse.end(); it++){
         // If the point is before the gap, then break here.
         if (prevCoord-gapLength < it->first){
            coord -= gapLength;
            break;
         }
         gapLength += it->second;
         // If removing the gap puts the x position before the gap, then it's directly on the gap.
         if (prevCoord-gapLength < it->first) return it->first;
      }
   } else {
      // Just add to the coordinate! 
      for (; it != toUse.end(); it++){
         // Check to see if the map coordinate is still after 
         // where the gap would be in map coordinates.
         if (it->first > prevCoord) break;
         coord += it->second;
      }
   }
   return coord;
}

std::vector<Level *> Map::updateLoadedLevels(GLUtil* glu){
   double newX = glu->draw->camX;
   double newY = glu->draw->camY;
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   return updateLoadedLevels(newX, newY, wid, hei);
}

std::vector<Level *> Map::updateLoadedLevels(double X, double Y, double W, double H){
   std::vector<Level *> levs;
   // Get the real x and y values by taking away the gaps.
   double rX = translateMapCoord(X, true, true);
   double rY = translateMapCoord(Y, false, true);
   // Check to see where we need to load a level.
   bool stillCamera = int(rX/32) == int(prevCX/32);
   stillCamera = stillCamera && int (rY/32) == int(prevCY/32);
   // Set the new camera posiiton.
   prevCX = rX;
   prevCY = rY;
   // If there's no place to check for a new level, just return.
   if (stillCamera && !firstLoad) return levs;
   levs = getUnloadedLevelsInArea(X-W*3/4, Y-H*3/4, W*5/2, H*5/2);
   firstLoad = false;
   return levs;
}

void Map::addGap(double P, double W, bool horiz, bool relative){
   std::map<double, double> toUse = horiz ? horizontalMapGap : verticalMapGap;
   std::map<double, double>::iterator gaps = toUse.begin();
   
   for (; gaps != toUse.end(); gaps++){
      double toCompare = gaps->first;
      if (abs(toCompare-P) < 0.001){
         toUse[toCompare] = W+relative?gaps->second:0;
         // Remove the gap if it's exactly 0.
         if (W == 0 && !relative){
            toUse.erase(toCompare);
         }
      } else if (toCompare > P && W != 0){
         toUse.insert(std::pair<double, double>(P, W));
         break;
      }
   }
}