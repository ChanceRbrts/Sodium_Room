#include "lighter.h"

Lighter::Lighter() : Instance(0, 0, 1, 1){
    maxFluid = 1;
    fluid = 1;
    cooldown = 0;
    maxCooldown = 10;
    prevAlpha = 1;
    newAlpha = 1;
    maxAnimTime = 1/15.0;
    animTime = maxAnimTime;
    a = new Arc(0, 0, 1, -M_PI, M_PI, 1, 1, 1, true);
    on = false;
    solid = false;
    name = "Lighter";
}

void Lighter::toggleLight(){
    if (!on && fluid < 0) return;
    on = !on;
}

void Lighter::lightFlicker(double deltaTime){
    // Make the alpha of the arc "flicker" sometimes.
    animTime += deltaTime;
    if (animTime >= maxAnimTime){
        // Set our new alpha point. (Mostly light, but flickering sometimes.)
        a->setAlpha(newAlpha);
        prevAlpha = newAlpha;
        double alphaPart = rand()*1.0/RAND_MAX;
        newAlpha = 0.25+0.75*pow(alphaPart, 0.25);
        animTime = 0;
    } else {
        // Let's do a sinusoildal regression; it should look natural?
        double avg = (prevAlpha+newAlpha)/2;
        double sinSize = (newAlpha-prevAlpha)/2;
        // This goes from prevAlpha to newAlpha; sin goes from 1 to -1.
        double nAlpha = avg-sinSize*sin(M_PI*animTime/maxAnimTime);
        a->setAlpha(nAlpha);
    }
}

void Lighter::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    // Toggle the lights.
    if (keyPressed[BUTTON_B]){
        toggleLight();
    }
    
    // Animation
    if (on) lightFlicker(deltaTime);
}
