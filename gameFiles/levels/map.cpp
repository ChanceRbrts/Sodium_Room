#include "map.h"

Map::Map(){
   x = 0;
   y = 0;
   w = 0;
   h = 0;
   prevCX = 0;
   prevCY = 0;
   superMapID = 0;
   firstLoad = true;
}

std::vector<LevLoaded> Map::getLevelsInArea(double p, double q1, double q2, bool horizontal, std::vector<LevLoaded> prev){
   for (int i = 0; i < levels.size(); i++){
      Level* l = levels[i];
      double lP = horizontal ? l->getXOff() : l->getYOff();
      double lQ = horizontal ? l->getYOff() : l->getXOff();
      double lP2 = lP + (horizontal ? l->w : l->h);
      double lQ2 = lQ + (horizontal ? l->h : l->w);
      if (p <= lP2 && p >= lP && q1 <= lQ2 && q2 >= lQ){
         // Check to make sure this level isn't already in the queue.
         bool loadIn = true;
         for (int j = 0; j < prev.size(); j++){
            if (prev[j].lev == l) loadIn = false;
         }
         if (loadIn) prev.push_back((LevLoaded){l, false});
      }
   }
   return prev;
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
   double checkX = X;
   double checkY = Y;
   if (!firstLoad){
      if (int(X/32) > int(prevCX/32)) checkX = X+W*7/4;
      if (int(X/32) < int(prevCX/32)) checkX = X-W*3/4;
      if (int(Y/32) > int(prevCY/32)) checkY = Y+H*7/4;
      if (int(Y/32) < int(prevCY/32)) checkY = Y-H*3/4;
   }
   // Set the new camera posiiton.
   prevCX = X;
   prevCY = Y;
   // If there's no place to check for a new level, just return.
   if (checkX == X && checkY == Y && !firstLoad) return levs;
   // Get the possible levels to load.
   std::vector<LevLoaded> toLoad;
   if ((firstLoad || checkX != X) && checkX >= x && checkX <= x+w &&
         Y-H*3/4 <= y+h && Y+H*7/4 >= y){
      toLoad = getLevelsInArea(checkX, Y-H*3/4, Y+H*7/4, true, toLoad);
   }
   if ((firstLoad || checkY != Y) && checkY >= y && checkY <= y+h &&
         X-W*3/4 <= x+w && X+W*7/4 >= x){
      toLoad = getLevelsInArea(checkY, X-W*3/4, X+W*7/4, false, toLoad);
   }
   firstLoad = false;
   if (toLoad.size() == 0) return levs;
   for (LevelList* lev = l; lev != nullptr; lev = lev->next){
      for (int i = 0; i < toLoad.size(); i++){
         // If the level has already been loaded, mark it as already loaded.
         if (!toLoad[i].loaded && toLoad[i].lev == lev->lev){
            toLoad[i].loaded = true;
         }
      }
   }
   // Return the levels that haven't been loaded in yet.
   for (int i = 0; i < toLoad.size(); i++){
      if (!toLoad[i].loaded){
         levs.push_back(toLoad[i].lev);
      }
   }
   toLoad.clear();
   return levs;
}