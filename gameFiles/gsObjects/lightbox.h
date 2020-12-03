#ifndef dwr_obj_lightbox
#define dwr_obj_lightbox

#include "../instance.h"

/**
 * A box that the player can "light up" with a lighter.
 * This light box will then have an arc that acts as a white light.
 * Should this be a "default" light like the lighter?
 */
class LightBox : public Instance {
    private:
        bool lit;
        float time, maxTime;
        Arc* a;
    public:
        LightBox(double X, double Y);
        std::vector<int> initLayers();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        Arc* getArc();
};

#endif