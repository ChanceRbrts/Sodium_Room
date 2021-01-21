#ifndef sdr_jung_bouncingfruit
#define sdr_jung_bouncingfruit

#include "../../instance.h"

class BouncingFruit : public Instance {
    private:
        bool facingRight;
        bool stopped;
        double speed;
    public:
        BouncingFruit(double X, double Y, bool goingRight);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        void collided(Instance* o, double deltaTime);
};

#endif