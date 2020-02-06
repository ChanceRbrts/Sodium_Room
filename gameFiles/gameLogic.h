#ifndef dos_gameLogic
#define dos_gameLogic

#include <fstream>
#include "instances.h"
#include "../main/shaderBox.h"
#include "levels/levels.h"
#include <map>

/**
 * This manages the game, going through update and draw loops.
 */
class GameLogic{
   private:
      bool madeBoxes, createdFonts;
      // The list of levels.
      Levels* levels;
      // The current level.
      Level* currentLevel;
      // The list of shaderboxes in the current level.
      std::vector<ShaderBox *> shaderboxes;
      // Instances are a linked list, so this is the start of it.
      Instances* head;
      // The player character.
      Instance* player;
      // Instances that are in the HUD.
      Instances* hud;
      // Last bit of the HUD.
      Instances* lastHud;
      // This allows you to add another instance to the linked list.
      Instances* addToList(Instances* prev, Instance* i);
      // This removes an instance from the linked list.
      void removeFromList(Instances* i);
   public:
      GameLogic();
      ~GameLogic();
      // Loads a level.
      void loadLevel();
      /**
       * The actual update loop. It goes through the current level and updates everything.
       * @param deltaTime The time in seconds since the previous frame.
       * @param glu The GLUtil class; Used only for the Controls right now.
       */
      void update(double deltaTime, GLUtil* glu);
      /**
       * Makes the camera follow the player.
       */
      void followPlayer(GLUtil* glu);
      /**
       * The actual draw loop. 
       * This goes through each of the shader boxes and draws stuff.
       * @param glu The GLUtil used to draw to the screen.
       */
      void draw(GLUtil* glu);
      /**
       * Draws things to the current camera.
       * @param glu The GLUtil used to draw to the screen.
       * @param mode I guess this does nothing right now? :\ Should determine whether or not to draw the player.
       */
      void drawObjects(GLUtil* glu, int mode);
      /**
       * Has the game create the shaderboxes for the current level.
       * @param glu The GLUtil that the shaderboxes will use for their drawing.
       */ 
      void createShaderBoxes(GLUtil* glu);
};

#endif