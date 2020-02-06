#ifndef dos_level_leveltemplate
#define dos_level_leveltemplate

#include "level.h"

class LevelTemplate : public Level{
   private:
      virtual std::vector<Instance*> makeLevel(std::vector<Instance*> previous);
   public:
      LevelTemplate();
      std::vector<ShaderBox *> createShaderBoxes(GLUtil* glu);
};

#endif