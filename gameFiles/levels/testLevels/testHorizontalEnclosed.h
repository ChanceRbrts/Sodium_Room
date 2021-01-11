#ifndef dwr_testHorizontalEnclosed
#define dwr_testHorizontalEnclosed

#include "../level.h"
#include "../../instancesExt.h"

class TestHorizontalEnclosed : public Level{
    private:
        double prevX;
        int ver;
        EnclosedLevel* encLev;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
    public:
        TestHorizontalEnclosed(int version);
        std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
        void updateLevel(double deltaTime, Instance* player);
};

class TestHorizontalInner : public Level{
    private:
        std::vector<Instance *>makeLevel(std::vector<Instance*> previous);
    public:
        TestHorizontalInner(int version);
};

#endif