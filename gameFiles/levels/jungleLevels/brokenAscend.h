#ifndef sdr_jung_brokenascend
#define sdr_jung_brokenascend

#include "../level.h"
#include "../../instancesExt.h"

class BrokenAscend : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        BrokenAscend();
};

#endif