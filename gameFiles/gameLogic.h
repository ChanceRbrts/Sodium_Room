#ifndef dos_gameLogic
#define dos_gameLogic

#include <fstream>
#include "instances.h"
#include "../main/shaderBox.h"
#include "../utils/texBook.h"
#include "levels/levels.h"
#include <map>
#include <algorithm>

/**
 * This manages the game, going through update and draw loops.
 */
class GameLogic{
   private:
      /// Whether or not fonts have been loaded into the game.
      bool createdFonts;
      /// The list of levels.
      Levels* levels;
      /// The loaded levels. (End of linked list)
      LevelList* loadedLevels;
      /// The level that has been loaded last.
      LevelList* lastLoaded;
      /// The player character.
      Instance* player;
      /// Instances that are in the HUD.
      Instances* hud;
      /// Last instance of the HUD. (End of linked list)
      Instances* lastHud;
      /// The camera of the level.
      Camera* camera;
      /// The shaderbox that the level draws to before the screen.
      ShaderBox* drawBox;
      DualSBox arcBoxOne;
      DualSBox arcBoxTwo;
      int curSMapID;
      /// Whether or not the camera's position has been set yet.
      bool loadedCam;
      /**
       * A simple linked list adder
       * @param prev The instances node to add to.
       * @param i The instance to add to the linked list.
       * @return The instances node that represents i.
       */
      Instances* addToList(Instances* prev, Instance* i);
      /**
       * This removes and instance from the linked list.
       * @param i The instance to remove.
       * @param start The start of the current linked list.
       */
      void removeFromList(Instances* i, Instances** start);
      /**
       * Modify which levels are currently loaded in.
       * @param glu The GLUtils (Used just to see what's in the camera.)
       */
      void modifyLevelsLoaded(GLUtil* glu);
      /**
       * The drawing layers that each level needs to draw to.
       * The idea is to draw instances in layers that are in numerical order.
       */
      std::map<int, std::vector<Layer *>> layers;
      /**
       * Creates a map that maps integers to layers within Levels to draw to the screen.
       * The idea is that the layers are drawn in numerical order.
       * @return A map that corresponds to <layerID, Layer> pairs.
       */
      std::map<int, std::vector<Layer *>> generateLayers();
      /// Whether or not the drawn layers need to be reloaded.
      bool reloadLayers;
      /// The current supermap that's being loaded.
      std::vector<Map *> superMap;
   public:
      /// The constructor of the GameLogic.
      GameLogic();
      /// The deconstructor of the GameLogic.
      ~GameLogic();
      /**
       * Load a map into the game.
       */
      void loadSuperMap(int mapID, double X, double Y, double W, double H);
      /**
       * Loads a level into the game
       * @param l The level to load.
       */
      void loadLevel(Level* l);
      /**
       * Removes a level from the game.
       * @param l The level to remove.
       */
      void unloadLevel(LevelList* l);
      /**
       * The actual update loop. It goes through the current level and updates everything.
       * @param deltaTime The time in seconds since the previous frame.
       * @param glu The GLUtil class; Used only for the Controls right now.
       */
      void update(double deltaTime, GLUtil* glu);
      /**
       * This updates the camera to it's next position.
       * @param deltaTime 
       * @param glu The GLUtil class; Used to update camX and camY.
       */
      void updateCamera(double deltaTime, GLUtil* glu);
      /**
       * Makes the camera follow the player.
       * @param glu The GLUtil class; Used to update camX and camY.
       */
      pointDouble followPlayer(GLUtil* glu);
      /**
       * The actual draw loop. 
       * This goes through each of the shader boxes and draws stuff.
       * @param glu The GLUtil used to draw to the screen.
       */
      void draw(GLUtil* glu);
};

#endif