#ifndef sdr_hub_firstfloor
#define sdr_hub_firstfloor

#include "../level.h"

class HubFirstFloor : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        HubFirstFloor();
        std::vector<Arc *> createArcs();
        std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
};

#endif