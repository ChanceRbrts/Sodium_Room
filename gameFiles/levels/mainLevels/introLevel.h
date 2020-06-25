#ifndef sdr_level_intro
#define sdr_level_intro
#include "../level.h"

class IntroLevel : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        std::vector<CameraObject *> createCameraObjects();
        InstCreate* iC;
    public:
        IntroLevel();
        ~IntroLevel();
        void updateLevel(double deltaTime, Instance* player);
};

#endif