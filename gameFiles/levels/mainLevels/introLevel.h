#ifndef sdr_level_intro
#define sdr_level_intro
#include "../level.h"

class IntroLevel : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        InstCreate* iC;
    public:
        IntroLevel();
        void updateLevel(double deltaTime, Instance* player);
};

#endif