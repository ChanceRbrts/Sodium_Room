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
      /** This function returns all of the objects in the room. (Called after createLevel) */
      virtual std::vector<Instance*> makeLevel(std::vector<Instance*> previous);
      /**
       * This function moves an instance from one level to another level.
       * @param move The Instance of this level to be moved into the other level.
       * @param otherLev The other level that we're comparing this to.
       */
      void moveInstance(Instances* move, Level* otherLev);
      // This function returns all of the shaderboxes in the room.
      virtual std::vector<ShaderBox*> createShaderBoxes(GLUtil* glu);
      // This draws the objects in the room.
      void drawObjects(GLUtil* glu, Instance* player, int mode);
   public:
      int w, h;
      float xOff, yOff;
      bool hasBackground;
      float r, g, b;
      bool createdShaderboxes;
      std::string filePath;
      Instances* insts;
      std::vector<ShaderBox*> shades;
      Level();
      ~Level();
      /** Build a level from a file directory. */
      pointDouble createLevel();
      void destroyLevel();
      void draw(GLUtil* glu, Instance* player);
      void moveOutOfBounds(void* lev);
};

/**
 * A simple doubly linked list for Levels.
 */
struct LevelList{
   Level* lev;
   LevelList* prev;
   LevelList* next;
};

#endif