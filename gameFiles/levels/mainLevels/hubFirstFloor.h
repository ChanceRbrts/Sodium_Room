#ifndef sdr_hub_firstfloor
#define sdr_hub_firstfloor

#include "../level.h"
#include "../../shaderboxes/longShaderbox.h"

class HubFirstFloor : public Level {
    private:
        double anim, maxAnim;
        double prevAlpha, newAlpha, dark;
        ShaderBox* darkRoom;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
        void updateLighting(double deltaTime);
    public:
        HubFirstFloor();
        std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
        void updateLevel(double deltaTime, Instance* player);
};

#endif