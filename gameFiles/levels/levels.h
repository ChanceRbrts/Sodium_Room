#ifndef dos_obj_levels
#define dos_obj_levels

#include "level.h"

// This is where DoS would put its generated levels.
#include "levelExample.h"
#include "testLevels/testRain.h"
#include "testLevels/testFalseBlocks.h"
#include "testLevels/testHorizontalEnclosed.h"
#include "testLevels/testJungleObjects.h"

class Levels{
   public:
      std::vector<Level *> lev;
      Levels();
};

#endif