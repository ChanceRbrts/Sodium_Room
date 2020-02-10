#ifndef dwr_enclosedlevel
#define dwr_enclosedlevel

#include "../instancelev.h"
#include <math.h>

class EnclosedLevel : public InstanceLev {
    private:
        bool openHorizontally;
        bool pushLevel;
        bool prevLevelUp, levelUp;
        float openTime, maxOpenTime;
        double trueW, lastW;
        Level* lev;
    public:
        bool open;
        EnclosedLevel(double X, double Y, double W, double H, Level* l);
        void drawEX(GLUtil* glu);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void messWithLevels(LevelList* levs, Instance* player);
};

#endif