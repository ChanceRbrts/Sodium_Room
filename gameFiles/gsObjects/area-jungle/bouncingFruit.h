#ifndef sdr_jung_bouncingfruit
#define sdr_jung_bouncingfruit

#include "../../instance.h"

class BouncingFruit : public Instance {
    private:
        bool facingRight;
        bool stopped;
        bool prevFaceBack;
        double speed;
        double speedup, maxSpeedup;
        double waitTime, maxWaitTime;
    public:
        BouncingFruit(double X, double Y, bool goingRight);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        void collided(Instance* o, double deltaTime);
};

class GiantFlower : public Instance {
    private:
        float makeLeaf;
        std::vector<int> initLayers();
    public:
        GiantFlower(double X, double Y);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
};

class Leaf : public Instance {
    private:
        float leafGrow, maxLeafGrow;
        bool gRight;
        std::vector<int> initLayers();
    public:
        Leaf(double X, double Y, bool growRight);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
};

class Soil : public Instance {
    public:
        Soil(double X, double Y, double W);
};

#endif