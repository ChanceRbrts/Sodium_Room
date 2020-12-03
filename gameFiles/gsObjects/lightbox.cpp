#include "lightbox.h"

LightBox::LightBox(double X, double Y) : Instance(X, Y, 2, 2){
    a = new Arc(X+1, Y+1, 0, -M_PI, M_PI, 1.1, 1.1, 1.1, false);
    lit = false;
    solid = false;
    time = 0;
    maxTime = 1;
}

std::vector<int> LightBox::initLayers(){
    std::vector<int> layers;
    layers.push_back(LAYER_NORMAL-1);
    return layers;
}

void LightBox::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    bool lighterColl = false;
    for (int i = 0; i < arcList.size(); i++){
        ArcInfo aI = arcList[i];
        // The player's lighter is the only thing with this default behavior and ID.
        if (aI.defBehavior && aI.id == -1){
            lighterColl = true;
        }
    }
    if (lighterColl){
        if (!lit && keyPressed[BUTTON_UP]){
            lit = true;
        } else if (lit && keyPressed[BUTTON_DOWN]){
            lit = false;
        }
    }
    // Make the lighter radius transition if it's there.
    if (lit && time < maxTime){
        time += deltaTime;
        if (time > maxTime) time = maxTime;
    } else if (!lit && time > 0){
        time -= 4*deltaTime;
        if (time < 0) time = 0;
    }
    // Adjust the arc of the lighter.
    a->setR(96*time/maxTime);
    a->setPosition(x+w/2, y+h/2);
}

Arc* LightBox::getArc(){
    return a;
}
