#include "lighter.h"

Lighter::Lighter() : PlayerAbility(0, 0, 1, 1){
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
    a = new Arc(0, 0, 4, -M_PI, M_PI, 1, 1, 1, false);
    a->makeDefault();
    on = false;
    solid = false;
    name = "Lighter";
}

Lighter::~Lighter(){
    delete a;
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
        double newColor = 1.0+0.25*((newAlpha-0.25)/0.75);
        a->setColor(newColor, newColor, newColor);
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
        cooldown += deltaTime;
        if (cooldown > maxCooldown) cooldown = maxCooldown;
    } else if (on){
        // Slowly diminish the lighter's radius.
        fluid -= deltaTime*diminishFactor;
        if (fluid < 0){
            fluid = 0;
            on = false;
        }
    } else if (fluid < maxFluid && cooldown < maxCooldown) {
        // Prioritize the lighter radius to the cooldown.
        fluid += deltaTime*incFactor;
        if (fluid > maxFluid) fluid = maxFluid;
    } else if (cooldown > 0){
        // Once we have a large lighter, increase the cooldown again.
        cooldown -= deltaTime*cooloffFactor;
        if (cooldown <= 0) cooldown = 0;
    }
}

void Lighter::fUpdate(double deltaTime){
    double trueR = 16+48*(fluid/maxFluid);
    a->setR(trueR == 0 ? 0.1 : trueR);
    double trueX = (trueR == 0 || !on) ? x-999 : x;
    a->setPosition(trueX, y);
}

void Lighter::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Rain") == 0 && on){
        // Rain makes things harder for a lighter.
        fluid -= deltaTime*meltFactor;
    }
}

void Lighter::draw(GLDraw* gld, GLShaders* gls, int layer){
    // Do some drawing code here at some point.
    // For now, do nothing.
}
