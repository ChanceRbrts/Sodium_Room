#include "levels.h"

Levels::Levels(){
   // Make the example map first.
   Map* example = new Map(MAP_EXAMPLE);
   example->addLevel(new LevelExample(), 0, 0);
   maps.push_back(example);
   // The intro map is just one room, which can just be added here.
   Map* intro = new Map(MAP_INTRO);
   intro->addLevel(new IntroLevel(), 0, 0);
   maps.push_back(intro);
   // Add the rest of the maps into a list.
   maps.push_back(new TestMap(MAP_TEST));
   maps.push_back(new TestMultipleRooms(MAP_TESTMULTIPLE));
   maps.push_back(new HubMap(MAP_MAIN));
   // maps.push_back(new JungleMap(MAP_MAIN));
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