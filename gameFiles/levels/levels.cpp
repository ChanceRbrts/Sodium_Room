#include "levels.h"

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
   Map* map = new Map();
   map->addLevel(lev[LEV_EXAMPLE], 0, 0);
   maps.push_back(map);
}

pairVector<Map*> Levels::getSuperMap(int superMapID, double offX, double offY, double wid, double hei){
   std::vector<Map *> superMap;
   std::vector<Map *> mapsAtOffset;
   for (int i = 0; i < maps.size(); i++){
      Map* map = maps[i];
      if (map->getSuperMapID() == superMapID){
         superMap.push_back(map);
      } else continue;
      if (map->inBounds(offX-wid*3/4, offY-hei*3/4, wid*5/2, hei*5/2)){
         mapsAtOffset.push_back(map);
      }
   }
   return (pairVector<Map*>){superMap, mapsAtOffset};
}

pairVector<Map*> Levels::getSuperMap(int superMapID, double offX, double offY, GLUtil* glu){
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   return getSuperMap(superMapID, offX, offY, wid, hei);
}