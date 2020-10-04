#ifndef dos_lev_map
#define dos_lev_map

#include "level.h"

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
      std::vector<Level *> getUnloadedLevelsInArea(double X, double Y, double W, double H);
      int superMapID;
   public:
      void addLevel(Level* l, double X, double Y);
      std::vector<Level *> updateLoadedLevels(LevelList* l, GLUtil* glu);
      std::vector<Level *> updateLoadedLevels(LevelList* l, double X, double Y, double W, double H);
      Map(int sID);
      virtual ~Map(){};
      int getSuperMapID(){ return superMapID; };  
      bool inBounds(double X, double Y, double W, double H);
};

#endif