#ifndef sdr_jung_lightboxescort
#define sdr_jung_lightboxescort

#include "../level.h"
#include "../../instancesExt.h"

class LightBoxEscort : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
        Level* en1;
        Level* en2;
        Level* en3;
        Level* en4;
    public:
        LightBoxEscort();
        std::vector<Arc *> createArcs(); 
};

#endif