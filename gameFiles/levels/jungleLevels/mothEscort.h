#ifndef sdr_jung_mothesc
#define sdr_jung_mothesc

#include "../level.h"

class MothEscort : public Level {
    private: 
        LightBox* light;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        void demakeLevel();
        std::vector<CameraObject *> createCameraObjects();
    public:
        MothEscort();
        std::vector<Arc *> createArcs(); 
};

#endif