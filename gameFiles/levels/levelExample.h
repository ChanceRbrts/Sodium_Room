#ifndef dos_level_levelexample
#define dos_level_levelexample

#include "level.h"
#include "../shaderboxes/longShaderbox.h"

class LevelExample : public Level{
   private:
      std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
   public:
      LevelExample();
      std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
      
};

#endif