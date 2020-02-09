#ifndef dwr_enclosedlevel
#define dwr_enclosedlevel

#include "../instance.h"
#include "../levels/level.h"

class EnclosedLevel : public Instance {
    private:
        bool open, openHorizontally;
        bool prevLevelUp, levelUp;
        float openTime, maxOpenTime;
        double trueW;
        Level* lev;
    public:
        EnclosedLevel(double X, double Y, double W, double H, Level* l);
        void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
};

#endif