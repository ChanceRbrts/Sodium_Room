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
}