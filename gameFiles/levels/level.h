#ifndef dos_game_level
#define dos_game_level

#include "../instances.h"
#include "../cameraObjects/cameraObjects.h"
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
      /** 
       * This function returns all of the objects in the room. (Called after createLevel) 
       * @param previous The instances of the level created before makeLevel
       * @return A list of instances for the level.
       */
      virtual std::vector<Instance*> makeLevel(std::vector<Instance*> previous);
      /**
       * This function moves an instance from one level to another level.
       * @param move The Instance of this level to be moved into the other level.
       * @param otherLev The other level that we're comparing this to.
       */
      void moveInstance(Instances* move, Level* otherLev);
      /**
       * This function returns all of the shaderboxes in the room.
       * @param glu The GLUtil to use for drawing.
       * @return A list of shaderboxes that are in the level.
       */
      virtual std::vector<ShaderBox*> createShaderBoxes(GLUtil* glu);
      /// @return A list of the arcs in the room.
      virtual std::vector<Arc*> createArcs();
      /// @return A list of the camera objects in the room.
      virtual std::vector<CameraObject*> createCameraObjects();
      /**
       * This draws the objects in the room
       * @param glu The GLUtil to use for drawing
       * @param player The player of the game
       * @param mode TODO: ? Whether or not to draw the player in the room or something?
       */
      void drawObjects(GLUtil* glu, Instance* player, int mode);
      /// The offset of where the instances are in the level.
      float xOff, yOff;
   public:
      /// The width and height of the level.
      float w, h;
      /// Whether or not the level actually has a background color.
      bool hasBackground;
      /// The background color of the level.
      float r, g, b;
      /// Whether or not we have created shaderboxes for this level.
      bool createdShaderboxes;
      /// The path to the file that generates the level.
      std::string filePath;
      /// The level's instances. 
      Instances* insts, lastInsts;
      /// Layers that tell us when to draw an instance.
      std::vector<Instances*> layers;
      /// The level's shaderboxes
      std::vector<ShaderBox*> shades;
      /// The level's arcs
      std::vector<Arc*> arcs;
      /// The level's camera objects.
      std::vector<CameraObject*> camObjs;
      /// A Constructor for the level.
      Level();
      /// A Deconstructor for the level.
      virtual ~Level();
      /// @return A level from a file specified by filePath
      pointDouble createLevel();
      /// Destroy the current level.
      void destroyLevel();
      /**
       * Draw the level
       * @param glu The GLUtil to use for drawing
       * @param player The player of the game
       */
      void draw(GLUtil* glu, Instance* player);
      /**
       * Checks to see if an instance is out of bounds, and moves it to another level if so.
       * @param lv The list of levels in loaded in the game.
       */
      void moveOutOfBounds(void* lev);
      /// @return The current x offset of the level.
      float getXOff();
      /// @return The current y offset of the level.
      float getYOff();
      /**
       * Runs some update code specific to the level.
       * @param deltaTime The time in between the previous frame and this frame.
       * @param player The player of the game.
       */
      virtual void updateLevel(double deltaTime, Instance* player);
      /**
       * Code to move the room.
       * @param newXOff The new x offset.
       * @param newYOff The new y offset.
       * @param relative Whether or not newXOff and newYOff are relative to the current offsets.
       */
      void moveRoom(float newXOff, float newYOff, bool relative);
      /**
       * Code to bisect the room.
       * @param horizontal Whether to bisect the room horizontally or vertically
       * @param splitLocation The x or y position to split every instance on.
       * @param offset How much to split the position by
       * @param cause The instance that's causing the split (so it doesn't accidentally move)
       */
      void bisectLevel(bool horizontal, float splitLocation, float offset, Instance* cause);
};

/**
 * A simple doubly linked list for Levels.
 */
struct LevelList{
   /// The current level
   Level* lev;
   /// The previous node of the linked list.
   LevelList* prev;
   /// The next node of the linked list.
   LevelList* next;
};

#endif