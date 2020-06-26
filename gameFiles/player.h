#ifndef dos_obj_player
#define dos_obj_player 

#include "instance.h"

/**
 * A class representing different abilities that the player will have.
 */
class PlayerAbility : public Instance{
   protected:
      /// An arc that may or may not be associated with the ability.
      Arc* a;
   public: 
      /**
       * Constructor for the player ability.
       * (X, Y, W, and H are in unit coordinates (Multiplied by 32 pixels))
       * @param X The left-most position of the ability.
       * @param Y The up-most position of the ability.
       * @param W The width of the ability.
       * @param H The height of the ability.
       */
      PlayerAbility(double X, double Y, double W, double H);
      /**
       * @return An arc that's associated with the current ability.
       */
      Arc* getArc(){ return a; };
};

/**
 * The Player Character!
 */
class Player : public Instance{
   private:
      /// Whether or not the player can move by controls.
      bool locked;
      /// If > 0, the player can be considered on ground. (Used for coyote jumps.)
      double onGroundTime;
      /// How long the player can hold down the jump button to get a larger jump.
      double jumpTime;
      /// The threshold for how long the player can buffer the jump button before hitting the ground. 
      double aPressTime;
      /// The previous dY
      double prevdY;
      /// The previous dX
      double prevdX;
      /// A multiplier on the acceleration of jumping.
      double jumpMultiplier;
      /// Whether or not the player starts jumping.
      bool jumpFrame;
      /// Whether or not the player is facing right.
      bool facingRight;
      /// The current ability for the player.
      PlayerAbility* curAbility;
   public:
      /**
       * The constructor of the player.
       * @param X The left-most position of the instance. (Unit coords)
       * @param Y The up-most position of the instance. (Unit coords)
       */
      Player(double X, double Y);
      /// @return Whether or not the player can move.
      bool isLocked();
      /**
       * Decide whether or not to lock the player
       * @param lock Whether or not the player is locked.
       */
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
      /// @return Whether or not the player is currently jumping.
      bool isJumping();
      /**
       * This changes the current jump multiplier.
       * @param j The multiplier for the acceleration of a jump.
       */
      void changeJumpMultiplier(double j);
      /// @return The current ability of the player.
      PlayerAbility* getAbility();
      /**
       * Give an ability to the player.
       * @param plAb The ability to give to the player.
       */
      void giveAbility(PlayerAbility* plAb);
      /// @return Whether or not the player is currently facing right.
      bool isFacingRight();
      /**
       * This is implemented so the PlayerAbility have collided behaviors.
       * @param o The instance that's being collided with.
       * @param deltaTime The time in between this frame and the previous frame.
       */
      void collided(Instance* o, double deltaTime);
};

#endif