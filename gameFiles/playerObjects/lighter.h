#ifndef dwr_player_lighter
#define dwr_player_lighter
#include "../instance.h"

class Lighter : public Instance {
    private:
        double fluid, maxFluid;
        double cooldown, maxCooldown;
        // This is used for animating the light to make it seem more "flame-like"
        double prevAlpha, newAlpha;
        double animTime, maxAnimTime;
        Arc* a;
        bool on;
        void toggleLight();
        void lightFlicker(double deltaTime);
    public:
        Lighter();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        Arc* getArc(){ return a; };
};

#endif