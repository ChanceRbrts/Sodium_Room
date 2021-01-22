#ifndef sdr_jung_growfruit
#define sdr_jung_growfruit

#include "../level.h"

class GrowFruit : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        GrowFruit();
};

#endif