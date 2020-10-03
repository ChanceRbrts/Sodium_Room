#ifndef dos_lev_map
#define dos_lev_map

#include "level.h"

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

#endif