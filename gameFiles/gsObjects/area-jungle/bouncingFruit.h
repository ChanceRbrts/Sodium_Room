#ifndef sdr_jung_bouncingfruit
#define sdr_jung_bouncingfruit

#include "../../instance.h"

class BouncingFruit : public Instance {
    private:
        bool facingRight;
        bool stopped;
        double speed;
        double speedup, maxSpeedup;
        double waitTime, maxWaitTime;
    public:
        BouncingFruit(double X, double Y, bool goingRight);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        void collided(Instance* o, double deltaTime);
};

class GiantFlower : public Instance {
    /// TODO: All of this, honestly.
    public:
        GiantFlower(double X, double Y);
};

class Soil : public Instance {
    public:
        Soil(double X, double Y, double W);
};

#endif