#ifndef dwr_testjungleobjects
#define dwr_testjungleobjects

#include "../level.h"

class TestJungleObjects : public Level{
    protected:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
        Arc* a1;
        int colorPicker;
        double sineWaveCounter;
    public:
        TestJungleObjects();
        std::vector<Arc *> createArcs();
        void updateLevel(double deltaTime, Instance* player);
};

#endif