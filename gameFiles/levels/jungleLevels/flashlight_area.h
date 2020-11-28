#ifndef sdr_jung_getflash
#define sdr_jung_getflash

#include "../level.h"

class FlashlightArea : public Level{
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        FlashlightArea();
};

class FlashlightUpperArea : public Level{
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        FlashlightUpperArea();
};

class FlashlightLowerArea : public Level{
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        FlashlightLowerArea();
};

#endif