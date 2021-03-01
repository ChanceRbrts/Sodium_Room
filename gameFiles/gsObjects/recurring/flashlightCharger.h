#ifndef sdr_recr_flashCharge
#define sdr_recr_flashCharge

#include "../../instance.h"
#include "../../player.h"
#include "../../playerObjects/flashlight.h"

class FlashlightCharger : public Instance {
    protected:
        std::vector<int> initLayers();
    public:
        FlashlightCharger(double X, double Y);
        void collided(Instance* o, double deltaTime);
};

#endif