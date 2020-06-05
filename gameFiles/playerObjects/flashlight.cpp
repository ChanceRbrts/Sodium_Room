#include "flashlight.h"

Flashlight::Flashlight() : PlayerAbility(0, 0, 1, 1){
    on = false;
    a = new Arc(0, 0, 8, -M_PI/8, M_PI/8, 1, 1, 1, false);
    upVal = 0;
    angleVel = 0.5;
    maxBattery = 15;
    battery = maxBattery;
}

Flashlight::~Flashlight(){
    delete a;
}

void Flashlight::moveFlashlight(double deltaTime, bool* keyHeld){
    // Just simple moving up and down code.
    if (keyHeld[BUTTON_UP] && !keyHeld[BUTTON_DOWN]){
        upVal -= deltaTime*angleVel;
        if (upVal < -1) upVal = -1;
    } else if (keyHeld[BUTTON_DOWN] && !keyHeld[BUTTON_UP]){
        upVal += deltaTime*angleVel;
        if (upVal > 1) upVal = 1;
    }
}

void Flashlight::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    if (keyPressed[BUTTON_B] && battery > 0) on = !on;
    if (on) moveFlashlight(deltaTime, keyHeld);
    if (on){
        battery -= deltaTime;
        if (battery < 0){
            battery = 0;
            on = false;
        }
    }
    double newAngle = M_PI*7/8*upVal;
    // Figure out which direction the arc is facing.
    newAngle = ((Player *)player)->isFacingRight() ? -newAngle : M_PI+newAngle;
    a->setAngle(newAngle-M_PI/8, newAngle+M_PI/8);
}

void Flashlight::fUpdate(double deltaTime){
    double trueX = !on ? x-999 : x;
    a->setPosition(trueX, y);
}

void Flashlight::draw(GLDraw* gld, GLShaders* gls){
    // Eventually, this will draw the flashlight.
    // However, for now, it will do nothing.
}
