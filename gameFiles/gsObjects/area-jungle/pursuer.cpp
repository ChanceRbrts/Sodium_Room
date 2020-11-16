#include "pursuer.h"

Pursuer::Pursuer(double X, double Y) : Instance(X, Y, 1, 1){
    radius = 96;   
}

void Pursuer::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    // Look at the list of arcs and make sure there's not one for green.
    bool pursue = true;
    for (int i = 0; i < arcList.size(); i++){
        if (arcList[i].g > 0.5 && arcList[i].r < 0.5 && arcList[i].b < 0.5){
            pursue = false;
        }
    }
    dX = 0;
    dY = 0;
    float difX = x+w/2-(player->x+player->w/2);
    float difY = y+h/2-(player->y+player->h/2);
    float dist = sqrt(difX*difX+difY*difY);
    if (dist < radius && pursue){
        float angle = atan2(difY, difX);
        dX = 96*cos(angle);
        dY = 96*sin(angle);
    }
}

void Pursuer::collided(Instance* o, double deltaTime){
    if (!o->isPlayer()) return;
    Player* p = (Player *)o;
    // Death animation or something?
}
