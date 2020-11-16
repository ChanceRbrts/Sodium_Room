#ifndef sdr_jung_pursuer
#define sdr_jung_pursuer

#include "../../instance.h"
#include "../../player.h"

class Pursuer : public Instance {
    private:
        double radius;
    public:
        Pursuer(double X, double Y);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void collided(Instance* o, double deltaTime);
};

#endif