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
   for (int i = 0; i < levels.size(); i++){
      Level* l = levels[i];
      double lX = l->getXOff();
      double lY = l->getYOff();
      double lW = l->w;
      double lH = l->h;
      if (X <= lX+lW && X+W >= lX && Y <= lY+lH && Y+H >= lY){
         if (!l->getLoaded()) levs.push_back(l);
      }
   }
   return levs;  
}

void Map::addLevel(Level* l, double X, double Y){
   l->moveRoom(X*32, Y*32, false);
   // pointInt area = (pointInt){(int)(X/100), (int)(Y/100), 0};
   if (levels.size() == 0){
      x = l->getXOff();
      y = l->getYOff();
      w = l->w;
      h = l->h;
   } else{
      float levX = l->getXOff();
      float levY = l->getYOff();
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
   return x <= X+W && x+w >= X && y <= Y+H && y+h >= Y;
}

std::vector<Level *> Map::updateLoadedLevels(LevelList* l, GLUtil* glu){
   double newX = glu->draw->camX;
   double newY = glu->draw->camY;
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   return updateLoadedLevels(l, newX, newY, wid, hei);
}

std::vector<Level *> Map::updateLoadedLevels(LevelList* l, double X, double Y, double W, double H){
   std::vector<Level *> levs;
   // Check to see where we need to load a level.
   bool stillCamera = int(X/32) == int(prevCX/32);
   stillCamera = stillCamera && int (Y/32) == int(prevCY/32);
   // Set the new camera posiiton.
   prevCX = X;
   prevCY = Y;
   // If there's no place to check for a new level, just return.
   if (stillCamera && !firstLoad) return levs;
   levs = getUnloadedLevelsInArea(X-W*3/4, Y-H*3/4, W*5/2, H*5/2);
   firstLoad = false;
   return levs;
}