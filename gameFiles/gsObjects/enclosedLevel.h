#ifndef dwr_enclosedlevel
#define dwr_enclosedlevel

#include "../instancelev.h"
#include <math.h>

class EnclosedLevel : public InstanceLev {
    private:
        bool open, openHorizontally;
        bool pushLevel;
        bool prevLevelUp, levelUp;
        float openTime, maxOpenTime;
        double trueW, lastW;
        Level* lev;
    public:
        EnclosedLevel(double X, double Y, double W, double H, Level* l);
        void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void messWithLevels(LevelList* levs, Instance* player);
};

#endif