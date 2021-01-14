#ifndef sdr_jung_flashPodium
#define sdr_jung_flashPodium

#include "../../instance.h"

class FlashlightPodium : public Instance {
    private:
        std::string podiumVarName;
        std::vector<bool> locks;
    public:
        FlashlightPodium(double X, double Y);
};

#endif