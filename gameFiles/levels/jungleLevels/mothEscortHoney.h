#ifndef sdr_jung_mothplushoney
#define sdr_jung_mothplushoney

#include "../level.h"
#include "../../instancesExt.h"

class MothEscortHoney : public Level {
    private: 
        double lightOffTime, maxLightOffTime;
        LightBox* light;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        void demakeLevel();
        std::vector<CameraObject *> createCameraObjects();
    public:
        MothEscortHoney();
        std::vector<Arc *> createArcs(); 
        void updateLevel(double deltaTime, Instance* player);
};

#endif