#ifndef dos_game_level
#define dos_game_level

#include "../instances.h"
#include "../../main/shaderBox.h"
#include <regex>

#define DEFAULT 0
#define TEXTURES 1
#define LAYOUT 2

/**
 * A basic level class.
 * This provides the instances and their layouts.
 */
class Level{
   private:
      virtual std::vector<Instance*> makeLevel(std::vector<Instance*> previous);
   public:
      int w, h;
      std::string filePath;
      Level(){filePath = "";};
      std::vector<Instance*> createLevel();
      // This function returns all of the objects in the room. (Called after createLevel)
      virtual std::vector<ShaderBox*> createShaderBoxes(GLUtil* glu);
};
#endif