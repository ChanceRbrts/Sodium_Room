#ifndef sdr_jung_mothesc
#define sdr_jung_mothesc

#include "../level.h"

class MothEscort : public Level {
    private: 
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        MothEscort();
        std::vector<Arc *> createArcs(); 
};

#endif