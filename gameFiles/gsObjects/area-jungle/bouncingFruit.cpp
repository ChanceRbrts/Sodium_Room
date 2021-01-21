#include "bouncingFruit.h"

BouncingFruit::BouncingFruit(double X, double Y, bool goingRight) : Instance(X, Y, 1, 1){
    r = 0.92;
    g = 0.63;
    b = 0.2;
    gravity = false;
    stopped = true;
    facingRight = goingRight;
    speed = 512;
    dX = speed*facingRight?1:-1;
    name = "Bouncing Fruit";
}

void BouncingFruit::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    /// TODO: How do arcs affect the Bouncing Fruit?
    if (dX == 0){
        facingRight = !facingRight;
        dX = speed*facingRight?1:-1;
    }
    if (onGround) dY = -400;
}

void BouncingFruit::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Soil") != 0) return;
    /// TODO: Plant the fruit, create a flower of some sort with a semi-transparent platform or something.
}
