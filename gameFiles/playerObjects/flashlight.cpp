#include "flashlight.h"

Flashlight::Flashlight() : PlayerAbility(0, 0, 1, 1){
    on = false;
    a = new Arc(0, 0, 8, -M_PI/8, M_PI/8, 1.25, 1.25, 1.25, false);
    upVal = 0;
    angleVel = 0.5;
    // For now, let's assume that the flashlight has a one-time use battery.
    // TODO: Be able to pick other batteries up.
    // batt = new Battery(1.25, 1.25, 1.25, 15);
    batts.push_back(new Battery(0.4, 0.4, 0.4, 15));
    currentBattery = 0;
    maxAnimTime = 1/15.0;
    animTime = maxAnimTime;
    facingRight = true;
    name = "Flashlight";
}

Flashlight::~Flashlight(){
    delete a;
    for (int i = 0; i < batts.size(); i++){
        if (batts[i] != nullptr){
            delete batts[i];
        }
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
    if (currentBattery >= batts.size()) return;
    /// TODO: Swap the batteries
    if (keyHeld[BUTTON_Y]){
        int incr = keyPressed[BUTTON_UP] ? -1 : (keyPressed[BUTTON_DOWN] ? 1 : 0);
        currentBattery = (currentBattery+incr)/batts.size();
    } else {
        moveFlashlight(deltaTime, keyHeld);
    }
    Battery* batt = batts[currentBattery];
    if (keyPressed[BUTTON_B] && batt != nullptr) on = !on;
    if (on && batt == nullptr){
        on = false;
    }
    // Battery Handling Code
    if (on){
        batt->changeArcColor(a);
        batt->decreaseBattery(deltaTime);
        double newBatt = batt->getBattery();
        if (newBatt <= 0){
            // If the battery life is 0, turn the flashlight off.
            // Don't remove the battery; It can be charged at stations.
            /// TODO: Create a HUD icon showing that battery is out of life.
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
    } else {
        a->setAlpha(0);
    }
    double newAngle = M_PI*7/8*upVal;
    if (facingRight && keyHeld[BUTTON_LEFT] && !keyHeld[BUTTON_RIGHT]){
        facingRight = false;
    } else if (!facingRight && !keyHeld[BUTTON_LEFT] && keyHeld[BUTTON_RIGHT]){
        facingRight = true;
    }
    // Figure out which direction the arc is facing.
    newAngle = facingRight ? newAngle : M_PI-newAngle;
    a->setAngle(newAngle-M_PI/8, newAngle+M_PI/8);
}

void Flashlight::fUpdate(double deltaTime){
    double trueX = !on ? x-999999 : x;
    a->setPosition(trueX, y);
}

void Flashlight::draw(GLDraw* gld, GLShaders* gls, int layer){
    // Eventually, this will draw the flashlight.
    // However, for now, it will do nothing.
}

void Flashlight::drawHUD(GLDraw* gld, GLShaders* gls){
}

std::vector<pointDouble> Flashlight::chargeBatteries(double deltaTime){
    std::vector<pointDouble> chargingBatteries;
    for (int i = 0; i < batts.size(); i++){
        if (batts[i]->getBattery() < 1.0){
            batts[i]->decreaseBattery(-5*deltaTime);
            pointDouble colors = batts[i]->getColor();
            chargingBatteries.push_back(colors);
        }
    }
    return chargingBatteries;
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
    if (battery <= 0) battery = 0;
    if (battery >= maxBattery) battery = maxBattery;
}

void Battery::chargeBattery(double deltaTime){
    decreaseBattery(maxBattery/5*deltaTime);
}

void Battery::changeArcColor(Arc* a){
    a->setColor(r, g, b);
}

pointDouble Battery::getColor(){
    return (pointDouble){r, g, b};
}
