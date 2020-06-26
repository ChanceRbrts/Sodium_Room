#include "player.h"

Player::Player(double X, double Y) : Instance(X, Y, 1, 1){
   r = 0.25;
   g = 0.5;
   gravity = true;
   onGroundTime = 0;
   playerRef = true;
   prevdX = 0;
   prevdY = 0;
   name = "Player";
   locked = false;
   jumpFrame = false;
   jumpMultiplier = 1;
   curAbility = nullptr;
   facingRight = true;
}

void Player::update(double deltaTime, bool* keyPressed, bool* keyHeld){
   // If we're in a cutscene or something like that, then we shouldn't control the Player from here.
   if (locked) return;
   jumpFrame = false;
   if (onGround){ 
      onGroundTime = 0.1;
      jumpMultiplier = 1;
   }
   onGroundTime = onGroundTime>0?onGroundTime-deltaTime:0;
   aPressTime = aPressTime>0?aPressTime-deltaTime:0;
   jumpTime = jumpTime>0?jumpTime-deltaTime:0;
   // Moving Horizontally
   if (keyHeld[BUTTON_LEFT] && !keyHeld[BUTTON_RIGHT]){
      if (dX < 0) facingRight = false;
      dX -= dX < 0 ? 384*deltaTime : 768*deltaTime;
      if (dX < -384) dX = -384;
   } else if (keyHeld[BUTTON_RIGHT] && !keyHeld[BUTTON_LEFT]){
      if (dX > 0) facingRight = true;
      dX += dX > 0 ? 384*deltaTime : 768*deltaTime;
      if (dX > 384) dX = 384;
   } else{
      if (dX > 0){
         dX -= 768*deltaTime;
         if (dX < 0) dX = 0;
      } else if (dX < 0){
         dX += 768*deltaTime;
         if (dX > 0) dX = 0;
      }
   }
   if (keyPressed[BUTTON_A]){
      aPressTime = 0.15;
   }
   // Jumping
   if (aPressTime > 0 && onGroundTime > 0){
      onGroundTime = 0;
      jumpTime = 0.2;
      jumpFrame = true;
   }
   // This allows us to jump with conditional height.
   if (keyHeld[BUTTON_A] && onGroundTime <= 0){
      // Was 384.
      dY = jumpTime>0?-340*jumpMultiplier:dY>0?dY-128*jumpMultiplier*deltaTime:dY;
   }
   // Keep dX and dY before collision checks here.
   prevdX = dX;
   prevdY = dY;
   if (curAbility != nullptr){
      curAbility->update(deltaTime, keyPressed, keyHeld, this);
   }
   // printf("%f, %f\n", dXModifier, dYModifier);
}

void Player::fUpdate(double deltaTime){
   if (locked) return;
   // If something stops you from jumping, stop checking for conditional height.
   if (prevdY < 0 && dY >= 0){
      jumpTime = 0;
   }
   // Make sure the special ability starts on the player.
   if (curAbility != nullptr){
      curAbility->x = x+w/2;
      curAbility->y = y+h/2;
   }
   if (curAbility != nullptr){
      curAbility->finishUpdate(deltaTime);
   }
}

void Player::lockPlayer(bool lock){
   locked = lock;
}

bool Player::isLocked(){
   return locked;
}

bool Player::isJumping(){
   return jumpFrame;
}

bool Player::isFacingRight(){
   return facingRight;
}

void Player::changeJumpMultiplier(double j){
   if (j <= 0) return;
   jumpMultiplier = j;
}

void Player::collided(Instance* o, double deltaTime){
   curAbility->collided(o, deltaTime);
}

void Player::giveAbility(PlayerAbility* plAb){
   curAbility = plAb;
}


PlayerAbility* Player::getAbility(){

   return curAbility;
}

PlayerAbility::PlayerAbility(double X, double Y, double W, double H) : Instance(X, Y, W, H){
   a = nullptr;
}
