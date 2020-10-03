#include "levels.h"

Levels::Levels(){
   // Make the example map first.
   Map* map = new Map(MAP_EXAMPLE);
   map->addLevel(new LevelExample(), 0, 0);
   maps.push_back(map);
   // Make the other maps now.
   maps.push_back(new TestMap(MAP_TEST));
   maps.push_back(new TestMultipleRooms(MAP_TESTMULTIPLE));
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