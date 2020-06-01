#include "lighter.h"

Lighter::Lighter() : Instance(0, 0, 1, 1){
    maxFluid = 1;
    fluid = maxFluid;
    // Lighter Mechanic Variables
    cooldown = 0;
    maxCooldown = 5;
    cooloffFactor = 0.5;
    meltFactor = 1;
    diminishFactor = 0.2;
    incFactor = 0.2;
    // Animation Variables
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
    // The lighter can't last forever, so let's figure out a cooldown system.
    if (on && cooldown < maxCooldown){
        // Start a timer for when we need to dimish the lighter.
        cooldown += deltaTime*cooloffFactor;
        if (cooldown > maxCooldown) cooldown = maxCooldown;
    } else if (on){
        // Slowly diminish the lighter's radius.
        fluid -= deltaTime*diminishFactor;
        if (fluid < 0){
            fluid = 0;
            on = false;
        }
    } else if (cooldown > 0){
        // Prioritize the cooldown to the lighter radius.
        cooldown -= deltaTime*cooloffFactor;
        if (cooldown <= 0) cooldown = 0;
    } else if (fluid < maxFluid) {
        // Once we have a stable lighter, increase the radius again.
        fluid += deltaTime*incFactor;
        if (fluid > maxFluid) fluid = maxFluid;
    }
    
}

void Lighter::fUpdate(double deltaTime){
    double trueR = 64*fluid/maxFluid;
    a->setR(trueR == 0 ? 0.1 : trueR);
    double trueX = trueR == 0 ? x-999 : x;
    a->setPosition(trueX, y);
}

void Lighter::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Rain") == 0){
        // Rain makes things harder for a lighter.
        fluid -= deltaTime*meltFactor;
    }
}
