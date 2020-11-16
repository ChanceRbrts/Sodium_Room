#ifndef sdr_jung_entry
#define sdr_jung_entry

#include "../level.h"

class JungleEntry : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        JungleEntry();
};

#endif