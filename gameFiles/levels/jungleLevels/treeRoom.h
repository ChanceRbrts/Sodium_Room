#ifndef sdr_jung_treeroom
#define sdr_jung_treeroom

#include "../level.h"
#include "../../instancesExt.h"

class TreeRoom : public Level{
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        TreeRoom();
};

#endif