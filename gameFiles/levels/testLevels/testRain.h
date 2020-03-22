#ifndef dwr_testRain
#define dwr_testRain

#include "../level.h"

class TestRain : public Level {
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
    public:
        TestRain();
        std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
        std::vector<Arc *> createArcs();
        void updateLevel(double deltaTime, Instance* player);
};

#endif