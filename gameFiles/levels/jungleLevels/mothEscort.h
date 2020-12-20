#ifndef sdr_jung_mothesc
#define sdr_jung_mothesc

#include "../level.h"
#include "../../instancesExt.h"

class MothEscort : public Level {
    private: 
        double time, maxTime;
        LightBox* light;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        void demakeLevel();
        std::vector<CameraObject *> createCameraObjects();
    public:
        MothEscort();
        std::vector<Arc *> createArcs(); 
        void updateLevel(double deltaTime, Instance* player);
};

#endif