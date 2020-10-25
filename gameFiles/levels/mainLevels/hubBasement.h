#ifndef sdr_hub_basement
#define sdr_hub_basement

#include "../level.h"
#include "../../shaderboxes/longShaderbox.h"

class HubBasement : public Level {
    private:
        ShaderBox* darkRoom;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
    public:
        HubBasement();
        std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu); 
        void updateLevel(double deltaTime, Instance* player);
};

#endif