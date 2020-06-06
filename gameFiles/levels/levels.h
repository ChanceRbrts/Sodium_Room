#ifndef dos_obj_levels
#define dos_obj_levels

#include "level.h"

// This is where DoS would put its generated levels.
#include "levelExample.h"
#include "testLevels/testRain.h"
#include "testLevels/testFalseBlocks.h"
#include "testLevels/testHorizontalEnclosed.h"
#include "testLevels/testJungleObjects.h"

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