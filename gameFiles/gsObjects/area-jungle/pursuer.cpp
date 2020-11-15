#include "pursuer.h"

Pursuer::Pursuer(double X, double Y) : Instance(X, Y, 1, 1){
    radius = 96;   
}

void Pursuer::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    dX = 0;
    dY = 0;
    float difX = x+w/2-(player->x+player->w/2);
    float difY = y+h/2-(player->y+player->h/2);
    float dist = sqrt(difX*difX+difY*difY);
    if (dist < radius){
        float angle = atan2(difY, difX);
        dX = 96*cos(angle);
        dY = 96*sin(angle);
    }
}
