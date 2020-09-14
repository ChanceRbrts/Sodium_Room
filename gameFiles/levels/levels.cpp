#include "levels.h"

Map::Map(){
   prevCX = 0;
   prevCY = 0;
}

std::vector<LevLoaded> Map::getLevelsInArea(double p, double q1, double q2, bool horizontal, std::vector<LevLoaded> prev){
   for (int i = 0; i < levels.size(); i++){
      Level* l = levels[i];
      double lP = horizontal ? l->getXOff() : l->getYOff();
      double lQ = horizontal ? l->getYOff() : l->getXOff();
      double lP2 = lP + (horizontal ? l->w : l->h);
      double lQ2 = lQ + (horizontal ? l->h : l->w);
      if (p <= lP2 && p >= lP && q1 <= lQ2 && q2 >= lQ){
         prev.push_back((LevLoaded){l, false});
      }
   }
   return prev;
}

void Map::addLevel(Level* l, double X, double Y){
   l->moveRoom(X*32, Y*32, false);
   pointInt area = (pointInt){X/100, Y/100, 0};
   levels.push_back(l);
}

std::vector<Level *> Map::updateLoadedLevels(LevelList* l, GLUtil* glu){
   double newX = glu->draw->camX;
   double newY = glu->draw->camY;
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   std::vector<Level *> levs;
   // Check to see where we need to load a level.
   bool checkX = newX;
   bool checkY = newY;
   if (int(newX/32) > int(prevCX/32)) checkX = newX+wid*7/4;
   if (int(newX/32) < int(prevCX/32)) checkX = newX-wid*3/4;
   if (int(newY/32) > int(prevCY/32)) checkY = newY+hei*7/4;
   if (int(newY/32) < int(prevCY/32)) checkY = newY-hei*3/4;
   // Set the new camera posiiton.
   prevCX = newX;
   prevCY = newY;
   // If there's no place to check for a new level, just return.
   if (checkX == newX && checkY == newY) return levs;

   // Get the possible levels to load.
   std::vector<LevLoaded> toLoad;
   if (checkX != newX && checkX >= x && checkX <= x+w &&
         newY-hei*3/4 <= y+h && newY+hei*7/4 >= y){
      toLoad = getLevelsInArea(checkX, newY-hei*3/4, newY+hei*7/4, true, toLoad);
   }
   if (checkY != newY && checkY >= y && checkY <= y+h &&
         newX-wid*3/4 <= x+w && newX+wid*7/4 >= x){
      toLoad = getLevelsInArea(checkY, newX-wid*3/4, newX+wid*7/4, false, toLoad);
   }
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

Levels::Levels(){
   // Add Levels Here
   lev.push_back(new LevelExample());
   lev.push_back(new TestRain());
   lev.push_back(new TestFalseBlocks());
   lev.push_back(new TestHorizontalEnclosed());
   lev.push_back(new TestJungleObjects());
   lev.push_back(new IntroLevel());
   lev.push_back(new RainHallwayLevel());
   lev.push_back(new TestMultipleLights());
}