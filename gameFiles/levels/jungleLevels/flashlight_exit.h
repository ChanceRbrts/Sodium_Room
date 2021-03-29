#ifndef sdr_jung_flashexit
#define sdr_jung_flashexit

#include "../level.h"
#include "../../instancesExt.h"

class FlashlightExit : public Level{
    private:
        Level* enclosed;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
        void demakeEnd();
    public:
        FlashlightExit();
};

#endif