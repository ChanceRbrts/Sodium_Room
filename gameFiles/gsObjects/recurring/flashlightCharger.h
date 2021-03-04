#ifndef sdr_recr_flashCharge
#define sdr_recr_flashCharge

#include "../../instance.h"
#include "../../player.h"
#include "../../playerObjects/flashlight.h"

#define AREA_JUNG 0

class FlashlightCharger : public Instance {
    protected:
        int frontTexture, backTexture;
        bool makeVisible, playerOnCharger;
        double visible, visibleSpeed, cyclePoint, transitionTime, maxTransitionTime;
        pointDouble chargeColor, prevChargeColor;
        std::vector<int> initLayers();
    public:
        FlashlightCharger(double X, double Y, int area);
        void collided(Instance* o, double deltaTime);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        void draw(GLDraw* gld, GLShaders* gls, int layer);
};

#endif