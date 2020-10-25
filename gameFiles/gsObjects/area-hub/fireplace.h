#ifndef dwr_hub_fireplace
#define dwr_hub_fireplace

#include "../../instance.h"

class Fireplace : public Instance {
    private:
        bool lit;
        std::string lName;
    public:
        Fireplace(double X, double Y, std::string litName);
        std::vector<int> initLayers();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
};

#endif