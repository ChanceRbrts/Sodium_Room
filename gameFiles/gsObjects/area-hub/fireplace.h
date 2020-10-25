#ifndef dwr_hub_fireplace
#define dwr_hub_fireplace

#include "../../instance.h"

class Fireplace : public Instance {
    public:
        Fireplace(double X, double Y);
        std::vector<int> initLayers();
};

#endif