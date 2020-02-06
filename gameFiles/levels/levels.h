#ifndef dos_obj_levels
#define dos_obj_levels
#include "levels.h"
// This is where DoS puts its generated levels.
#include "levelExample.h"
#include "testLevels/testRain.h"
#include "testLevels/testFalseBlocks.h"

class Levels{
   public:
      std::vector<Level *> lev;
      Levels();
};

#endif