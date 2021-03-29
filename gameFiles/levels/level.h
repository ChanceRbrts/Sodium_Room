#ifndef dos_game_level
#define dos_game_level

#include "../instances.h"
#include "../cameraObjects/cameraObjects.h"
#include "../../main/shaderBox.h"
#include <regex>

#define DEFAULT 0
#define TEXTURES 1
#define COLLMAP 2
#define LAYOUT 3

class Level;

/**
 * A pointer to a Instances list with the beginning and end attached to it.
 * This is used for 
 */
struct Layer{
   /// The level this layer belongs to.
   Level* lev;
   /// The instance that's at the beginning of the list.
   DrawnInstance* first;
   /// The instance that's at the end of the list.
   DrawnInstance* last;
};

/**
 * A basic level class.
 * This provides the instances and their layouts.
 */
class Level{
   private:
      /// A list of points of horizontal bisects to add.
      std::map<double, double> hBisectPoints; 
      /// A list of points of vertical bisects to add.
      std::map<double, double> vBisectPoints;
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
       * @return Whether or not the draw order needs to be changed.
       */
      bool moveInstance(Instances* move, Level* otherLev);
      /**
       * This function returns all of the shaderboxes in the room.
       * @param glu The GLUtil to use for drawing.
       * @return A list of shaderboxes that are in the level.
       */
      virtual std::vector<ShaderBox*> createShaderBoxes(GLUtil* glu);
      /**
       * Draws all layers and possibly the arcs to the screen at once.
       * Used only for drawing to a shaderbox.
       * @param glu The GLUtil to use for drawing.
       * @param player The player of the game.
       * @param drewArcs Whether or not arcs have been drawn to the screen yet.
       * @param shade The shaderbox that's currently being drawn to.
       */
      void fullDraw(GLUtil* glu, Instance* player, bool drawArcs, ShaderBox* shade);
      /// @return A list of the arcs in the room.
      virtual std::vector<Arc*> createArcs();
      /// @return A list of the camera objects in the room.
      virtual std::vector<CameraObject*> createCameraObjects();
      /// Do some level-specific de-allocation
      virtual void demakeLevel(){}
      /// Level-specific de-allocation that needs to be done after all instances are deleted.
      virtual void demakeEnd(){}
      /**
       * This draws the objects in the room
       * @param glu The GLUtil to use for drawing
       * @param mode TODO: ? Whether or not to draw the player in the room or something?
       */
      void drawObjects(GLUtil* glu, int layer, int mode);
      /// The offset of where the instances are in the level.
      float xOff, yOff;
      /// The offset of where the level is in the map.
      float mXOff, mYOff;
      /// The layers that are being drawn to in the level, and the instances of which to draw the layers on.
      std::map<int, Layer *> layers;
      /// Whether or not the level has been currently loaded.
      bool loaded;
      /// Whether or not the level doesn't get unloaded by the game logic.
      bool global;
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
      /// The level's shaderboxes (Drawn after arcs)
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
       * Draw the level at the current drawing layer.
       * It is assumed that the drawing layer will numerically increase.
       * @param glu The GLUtil to use for drawing
       * @param layer The layer that is being drawn to.
       */
      void drawLayer(GLUtil* glu, int layer);
      /**
       * Draw the arcs into the scene.
       * @param glu The GLUtil to use for drawing.
       * @param mainBox The shaderbox that was drawn to with the drawLayer steps.
       * @param arcOne The first shaderbox that the arcs draw to.
       * @param arcTwo The second shaderbox that the arcs draw to.
       * @param player The player object if it has an arc that needs to be drawn WITH this level.
       * @return Whether or not arcOne is the final shaderbox that was drawn to.
       */
      bool drawArcs(GLUtil* glu, ShaderBox* mainBox, DualSBox arcOne, DualSBox arcTwo, Instance* player);
      /**
       * Draw the shaderboxes in the level.
       * @param glu The GLUtil to use for drawing.
       * @param player The player of the game.
       * @param drewArcs The phase of the shaderbox corresponding to the arcs (0=Before, 1=Replace, 2=After)
       * @param screen The shaderbox that corresponds to the current screen.
       */
      void drawShaderboxes(GLUtil* glu, Instance* player, int drewArcs, ShaderBox* screen);
      /**
       * Checks to see if an instance is out of bounds, and moves it to another level if so.
       * @param lv The list of levels in loaded in the game.
       * @return Whether or not the drawing order needs to be changed.
       */
      bool moveOutOfBounds(void* lev);
      /// @return The current x offset of the level.
      float getXOff();
      /// @return The current y offset of the level.
      float getYOff();
      /// @return The x placement on the map this belongs to.
      float getMXOff();
      /// @return The y placement on the map this belongs to.
      float getMYOff();
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
       * Code to move the room in regards to a map.
       * @param newXOff The new x offset.
       * @param newYOff The new y offset.
       * @param relative Whether or not newXOff and newYOff are relative to the current offsets.
       */
      void moveInMap(float newXOff, float newYOff, bool relative);
      /**
       * Code to say "bisect the room when it's created!"
       * @param horizontal Whether to bisect the room horizontally or vertically.
       * @param splitLocation The point to split on.
       * @param offset How far to split the room.
       */
      void startBisect(bool horizontal, float splitLocation, float offset);
      /**
       * Code to bisect the room.
       * @param horizontal Whether to bisect the room horizontally or vertically
       * @param splitLocation The x or y position to split every instance on.
       * @param offset How much to split the position by
       * @param cause The instance that's causing the split (so it doesn't accidentally move)
       */
      void bisectLevel(bool horizontal, float splitLocation, float offset, Instance* cause);
      /**
       * @param prevLayers Layers that are already needed to be drawn to. 
       * @return The layers that need to be drawn.
       */
      std::map<int, std::vector<Layer *>> getLayers(std::map<int, std::vector<Layer *>> prevLayers);
      /**
       * Add an instance to the drawn layers of the current level.
       * @param in Contains the instance to add to be drawn to this level.
       * @return If a new layer has been added to the instance. If so, the layers to be drawn may need to be updated.
       */
      bool addToLayers(Instances* in);
      /**
       * Assumption: The instance being removed is from the current level.
       * Remove an instance from the drawn layers of the current level.
       * @param in Contains the instance to remove from this level.
       * @return If a layer has been removed from the instance. If so, the layers to be drawn may need to be updated.
       */
      bool removeFromLayers(Instances* in);
      /// @return Whether or not the level has been loaded.
      bool getLoaded();
      /// @param g Whether or not the level can't get unloaded by the game logic.
      void setGlobal(bool g);
      /// @return Whether or not the level can't get unloaded by the game logic.
      bool getGlobal();
      /// Read the file path to set the width and height of the level.
      void setWidthHeight();
};

/**
 * This is a simple level.
 * It contains a filename leading to a solid map and player X and Y coordinates.
 */
class BasicLevel : public Level {
   private:
      /// The x-coordinate of the player.
      double playerX;
      /// The y-coordinate of the player.
      double playerY;
      std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
   public:
      /**
       * Creates a level with just a solid map and a player.
       * @param fName The filename where the solid map provides.
       * @param pX The player's X position in world coords.
       * @param pY The player's Y position in world coords.
       */
      BasicLevel(std::string fName, double pX, double pY);
      /**
       * Creates a level with just a solid map and a player.
       * @param fName The filename where the solid map provides.
       * @param pX The player's X position in world coords.
       * @param pY The player's Y position in world coords.
       * @param R The red color of the background.
       * @param G The green color of the background.
       * @param B The blue color of the background.
       */
      BasicLevel(std::string fName, double pX, double pY, double R, double G, double B);
};

// Defined in map.h
class Map;

/**
 * A simple doubly linked list for Levels.
 */
struct LevelList{
   /// The current level
   Level* lev;
   /// The map that the level came from.
   Map* map;
   /// The previous node of the linked list.
   LevelList* prev;
   /// The next node of the linked list.
   LevelList* next;
};

#endif