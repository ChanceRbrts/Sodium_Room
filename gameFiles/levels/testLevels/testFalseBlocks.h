#ifndef dwr_testFalseBlocks
#define dwr_testFalseBlocks

#include "../level.h"

class TestFalseBlocks : public Level {
    private:
      std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
   public:
      TestFalseBlocks();
      std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
};

#endif