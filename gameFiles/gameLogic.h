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
      bool createdFonts;
      // The list of levels.
      Levels* levels;
      // The loaded levels.
      LevelList* loadedLevels;
      LevelList* lastLoaded;
      // The player character.
      Instance* player;
      // Instances that are in the HUD.
      Instances* hud;
      // Last bit of the HUD.
      Instances* lastHud;
      // This allows you to add another instance to the linked list.
      Instances* addToList(Instances* prev, Instance* i);
      // This removes an instance from the linked list.
      void removeFromList(Instances* i, Instances** start);
   public:
      GameLogic();
      ~GameLogic();
      // Loads a level.
      void loadLevel(Level* l);
      void unloadLevel(LevelList* l);
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
};

#endif