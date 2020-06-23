#include "cameraObjects.h"

CameraObject::CameraObject(){}

OneWayCameraObject::OneWayCameraObject(double X, double Y, double W, int direction) : CameraObject(){
    x = X*32;
    y = Y*32;
    w = W*32;
    dir = direction;
}

void OneWayCameraObject::modifyCamera(Camera* c, double deltaTime){
    double p = dir%2 == 0 ? c->getX() : c->getY();
    double* dP = dir%2 == 0 ? &(c->dX) : &(c->dY);
    double lim = dir%2 == 0 ? x : y;
    int sign = dir/2 == 0 ? 1 : -1;
    if (p*sign >= lim && (p+*dP*deltaTime)*sign > lim){
        *dP = (lim*sign-p)/deltaTime;
    }
}
