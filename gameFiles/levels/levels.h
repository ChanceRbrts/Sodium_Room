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
#include "testLevels/testMultipleLights.h"

// Do stuff in order
#define LEV_EXAMPLE 0
#define LEV_TEST_RAIN 1
#define LEV_TEST_FALSEBLOCKS 2
#define LEV_TEST_HORIZONTALENCLOSED 3
#define LEV_TEST_JUNGLEOBJECTS 4
#define LEV_MAIN_INTROLEVEL 5
#define LEV_JUNG_RAINHALLWAY 6
#define LEV_TEST_MULTILIGHTS 7

struct LevLoaded{
   Level* lev;
   bool loaded;
};

class Map{
   private:
      double x;
      double y;
      double prevCX;
      double prevCY;
      double w;
      double h;
      bool firstLoad;
      /// TODO: Find a better way to load levels besides iterating through every level.
      std::vector<Level *> levels;
      std::vector<LevLoaded> getLevelsInArea(double p, double q1, double q2, bool horizontal, std::vector<LevLoaded> prev);
      int superMapID;
   public:
      void addLevel(Level* l, double X, double Y);
      std::vector<Level *> updateLoadedLevels(LevelList* l, GLUtil* glu);
      std::vector<Level *> updateLoadedLevels(LevelList* l, double X, double Y, double W, double H);
      Map();
      int getSuperMapID(){ return superMapID; };  
      bool inBounds(double X, double Y, double W, double H);
};

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
      /// The list of levels
      std::vector<Level *> lev;
      std::vector<Map *> maps;
      /// A list of adjacent levels.
      std::map<int, std::vector<AdjLevel *>> adj;
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