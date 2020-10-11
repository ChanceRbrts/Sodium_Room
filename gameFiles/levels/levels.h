#ifndef dos_obj_levels
#define dos_obj_levels

#include "level.h"
#include "map.h"

// This is where DoS would put its generated levels.
#include "levelExample.h"
#include "testLevels/testRain.h"
#include "testLevels/testFalseBlocks.h"
#include "testLevels/testHorizontalEnclosed.h"
#include "testLevels/testJungleObjects.h"
#include "mainLevels/introLevel.h"
#include "jungleLevels/rainHallway.h"
#include "testLevels/testMultipleLights.h"

// Put all of the maps that will be used here.
#include "testLevels/testMap.h"
#include "jungleLevels/jungleMap.h"

// Generate IDs for all of the maps.
#define MAP_EXAMPLE 0
#define MAP_TEST 1
#define MAP_TESTMULTIPLE 2
#define MAP_INTRO 3
#define MAP_MAIN 4

// Do stuff in order
#define LEV_EXAMPLE 0
#define LEV_MAIN_INTROLEVEL 0

/// TODO: Find a better home for this.
template <class T>
struct pairVector{
   std::vector<T> a;
   std::vector<T> b;
};

/**
 * A simple list of all the levels.
 */
class Levels{
   public:
      /// A list of all of the maps.
      std::vector<Map *> maps;
      /// The constructor of the levels.
      Levels();
      /**
       * @param superMapID The ID of the super map to use.
       * @param offX The (estimated ?) xOffset of the level to load.
       * @param offY The (estimated ?) yOffset of the level to load.
       * @param wid The width of the screen.
       * @param hei The height of the screen.
       * @return (The maps in the supermap, the maps that should be loaded given the offset)
       */
      pairVector<Map*> getSuperMap(int superMapID, double offX, double offY, double wid, double hei);
      /**
       * @param superMapID The ID of the super map to use.
       * @param offX The (estimated ?) xOffset of the level to load.
       * @param offY The (estimated ?) yOffset of the level to load.
       * @param glu The GLUtils class. Used to get the width and the height of the screen.
       * @return (The maps in the supermap, the maps that should be loaded given the offset)
       */
      pairVector<Map*> getSuperMap(int superMapID, double offX, double offY, GLUtil* glu);
};

#endif