#ifndef dos_obj_player
#define dos_obj_player 

#include "instance.h"

/**
 * The Player Character!
 */
class Player : public Instance{
   private:
      bool locked;
      double onGroundTime;
      double jumpTime;
      double aPressTime;
      double prevdY;
      double prevdX;
      double jumpMultiplier;
      bool jumpFrame;
   public:
      Player(double X, double Y);
      bool isLocked();
      void lockPlayer(bool lock);
      /**
       * The update function for the player.
       * Controls movement and jumping currently.
       * @param deltaTime The time in between this frame and the previous frame.
       * @param keyPressed The array of keys pressed this frame.
       * @param keyHeld The array of the keys that are held down. 
       */
      void update(double deltaTime, bool* keyPressed, bool* keyHeld);
      /**
       * Doing checks on speed changes to alter some timers.
       * I probably could have done this with stuff in collided.
       */
      void fUpdate(double deltaTime);
      bool isJumping();
      void changeJumpMultiplier(double j);
};

#endif