#include "levels.h"

Levels::Levels(){
   // Add Levels Here
   lev.push_back(new LevelExample());
   lev.push_back(new TestRain());
   lev.push_back(new TestFalseBlocks());
   lev.push_back(new TestHorizontalEnclosed());
}