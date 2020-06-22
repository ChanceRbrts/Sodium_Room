#ifndef dos_obj_levels
#define dos_obj_levels

#include "level.h"

// This is where DoS would put its generated levels.
#include "levelExample.h"
#include "testLevels/testRain.h"
#include "testLevels/testFalseBlocks.h"
#include "testLevels/testHorizontalEnclosed.h"
#include "testLevels/testJungleObjects.h"
#include "mainLevels/introLevel.h"
#include "jungleLevels/rainHallway.h"

// Do stuff in order
#define LEV_EXAMPLE 0
#define LEV_TEST_RAIN 1
#define LEV_TEST_FALSEBLOCKS 2
#define LEV_TEST_HORIZONTALENCLOSED 3
#define LEV_TEST_JUNGLEOBJECTS 4
#define LEV_MAIN_INTROLEVEL 5
#define LEV_JUNG_RAINHALLWAY 6

/**
 * A simple list of all the levels.
 */
class Levels{
   public:
      /// The list of levels
      std::vector<Level *> lev;
      /// The constructor of the levels.
      Levels();
};

#endif