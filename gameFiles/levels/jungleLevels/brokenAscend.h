#ifndef sdr_jung_brokenascend
#define sdr_jung_brokenascend

#include "../level.h"
#include "../../instancesExt.h"

class BrokenAscend : public Level {
    private:
        Level* layer1;
        Level* layer2;
        Level* layer3;
        Level* layer4;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
        void demakeEnd();
    public:
        BrokenAscend();
};

#endif