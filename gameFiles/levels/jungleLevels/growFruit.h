#ifndef sdr_jung_growfruit
#define sdr_jung_growfruit

#include "../level.h"
#include "../../instancesExt.h"

class GrowFruit : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        GrowFruit();
        std::vector<Arc *> createArcs();
};

#endif