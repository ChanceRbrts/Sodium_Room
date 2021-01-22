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
    speedup = 0.5;
    maxSpeedup = 0.5;
    waitTime = 0;
    maxWaitTime = 0.25;
    name = "Bouncing Fruit";
}

void BouncingFruit::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    /// TODO: How do arcs affect the Bouncing Fruit?
    if (dX == 0){
        facingRight = !facingRight;
        speedup = 0;
    }
    dX = speed*speedup*(facingRight?1:-1);
    if (onGround){
        waitTime += deltaTime;
        dX *= 0.25;
        if (waitTime > maxWaitTime){
            waitTime = 0;
            dY = -400;
        }
    }
    if (waitTime <= 0 && speedup < maxSpeedup){
        speedup += deltaTime;
        if (speedup > maxSpeedup) speedup = maxSpeedup;
    }
}

void BouncingFruit::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Soil") != 0) return;
    /// TODO: Plant the fruit, create a flower of some sort with a semi-transparent platform or something.
}

Soil::Soil(double X, double Y, double W) : Instance(X, Y, W, 1){
    name = "Soil";
    immovable = true;
    r = 0.35;
    g = 0.23;
    b = 0.09;
}
