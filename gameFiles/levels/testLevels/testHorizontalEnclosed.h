#ifndef dwr_testHorizontalEnclosed
#define dwr_testHorizontalEnclosed

#include "../level.h"
#include "../../instancesExt.h"

class TestHorizontalEnclosed : public Level{
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
    public:
        TestHorizontalEnclosed();
        std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
};

class TestHorizontalInner : public Level{
    private:
        std::vector<Instance *>makeLevel(std::vector<Instance*> previous);
    public:
        TestHorizontalInner();
};

#endif