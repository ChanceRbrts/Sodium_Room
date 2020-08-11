#include "flashlight.h"

Flashlight::Flashlight() : PlayerAbility(0, 0, 1, 1){
    on = false;
    a = new Arc(0, 0, 8, -M_PI/8, M_PI/8, 1.25, 1.25, 1.25, false);
    upVal = 0;
    angleVel = 0.5;
    // For now, let's assume that the flashlight has a one-time use battery.
    // TODO: Be able to pick other batteries up.
    batt = new Battery(1, 1, 1, 15);
    maxAnimTime = 1/15.0;
    animTime = maxAnimTime;
}

Flashlight::~Flashlight(){
    delete a;
    if (batt != nullptr){
        delete batt;
    }
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
    if (keyPressed[BUTTON_B] && batt != nullptr) on = !on;
    moveFlashlight(deltaTime, keyHeld);
    if (on && batt == nullptr){
        on = false;
    }
    // Battery Handling Code
    if (on){
        batt->decreaseBattery(deltaTime);
        double newBatt = batt->getBattery();
        if (newBatt <= 0){
            // If the battery life is 0, turn the flashlight off.
            delete batt;
            batt = nullptr;
            on = false;
        } else if (newBatt < 0.25){
            animTime -= deltaTime;
            // If the battery is running low, do a flickering animation.
            if (animTime < 0){
                animTime = maxAnimTime;
                double randNum = (rand()*1.0/RAND_MAX);
                curAlpha = 0.25+0.75*pow(randNum, 0.25);
            }
            a->setAlpha(curAlpha);
        } else{
            // Otherwise, act as normal.
            a->setAlpha(1);
        }
    }
    double newAngle = M_PI*7/8*upVal;
    // Figure out which direction the arc is facing.
    newAngle = ((Player *)player)->isFacingRight() ? newAngle : M_PI-newAngle;
    a->setAngle(newAngle-M_PI/8, newAngle+M_PI/8);
}

void Flashlight::fUpdate(double deltaTime){
    double trueX = !on ? x-999 : x;
    a->setPosition(trueX, y);
}

void Flashlight::draw(GLDraw* gld, GLShaders* gls, int layer){
    // Eventually, this will draw the flashlight.
    // However, for now, it will do nothing.
}

Battery::Battery(double R, double G, double B, double mB){
    r = R;
    g = G;
    b = B;
    maxBattery = mB;
    battery = maxBattery;
}

double Battery::getBattery(){
    return battery/maxBattery;
}

void Battery::decreaseBattery(double deltaTime){
    battery -= deltaTime;
}
