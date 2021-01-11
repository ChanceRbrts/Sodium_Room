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

/// A variation of Moth Escort to use the flashlight instead of the lighter.
class MothEscort2 : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        MothEscort2();
        std::vector<Arc *> createArcs();
};

#endif