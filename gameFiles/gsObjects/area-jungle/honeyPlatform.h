#ifndef dwr_jungle_platform
#define dwr_jungle_platform

#include "../../instance.h"
#include "../../player.h"

class HoneyPlatform : public Instance {
    private:
        // The amount of time it takes for the color of the object to go from 0 to 255.
        double colorSwapTime;
        double moveValueTo(double* vMove, double vTo, double deltaTime);
        std::map<Instance *, bool> collidedInstances;
        bool changedColor;
    public:
        HoneyPlatform(double X, double Y, double W, bool horizontal);
        // void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        void collided(Instance* o, double deltaTime);
};

#endif