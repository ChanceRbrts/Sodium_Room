#include "cameraObjects.h"

Camera::Camera(){
    x = 0;
    y = 0;
    dX = 0;
    dY = 0;
    tarX = 0;
    tarY = 0;
    diffX = 0;
    diffY = 0;
    progressX = 0;
    progressY = 0;
    animTime = -1;
    maxAnimTime = 1;
}

void Camera::setTarget(double targetX, double targetY){
    tarX = targetX;
    tarY = targetY;
}

void Camera::setPosition(double X, double Y){
    x = X;
    y = Y;
    tarX = x;
    tarY = y;
}

void Camera::startMovement(double deltaTime){
    dX = (tarX-x)/deltaTime;
    dY = (tarY-y)/deltaTime;
}

void Camera::finishMovement(double deltaTime, bool loaded){
    if (!loaded){
        x += dX*deltaTime;
        y += dY*deltaTime;
        return;
    }
    // If we have an animation, update that.
    if (animTime >= 0){
        dX -= (diffX-progressX)/deltaTime;
        dY -= (diffY-progressY)/deltaTime;
    }
    int xSign = dX > 0 ? 1 : -1;
    int ySign = dY > 0 ? 1 : -1;
    // See if we need to go across a large distance (18px/frame or higher) and account for that.
    if (dX*xSign > 1080 || dY*ySign > 1080){
        diffX = diffX-progressX+dX*deltaTime;
        diffY = diffY-progressY+dY*deltaTime;
        // 1080/60 = 18
        if (abs(diffX) < 18 && abs(diffY) < 18){
            // The camera doesn't have to jump a large distance anymore.
            x += dX*deltaTime;
            y += dY*deltaTime;
            animTime = -1;
            return;
        }
        progressX = 0;
        progressY = 0;
        dX = 0;
        dY = 0;
        animTime = 0;
    }
    x += dX*deltaTime;
    y += dY*deltaTime;
    if (animTime < 0) return;
    // If we have a large gap, start the animation for that.
    animTime += deltaTime;
    if (animTime > maxAnimTime) animTime = maxAnimTime;
    // Move camera to the next distance.
    double totalDistMod = pow(sin(M_PI/2*animTime/maxAnimTime), 2);
    double nextDistX = diffX*totalDistMod-progressX;
    x += nextDistX;
    progressX += nextDistX;
    double nextDistY = diffY*totalDistMod-progressY;
    y += nextDistY;
    progressY += nextDistY;
    // Once we're done with the animation, stop it.
    if (animTime >= maxAnimTime) animTime = -1;
}

CameraObject::CameraObject(){}

OneWayCameraObject::OneWayCameraObject(double X, double Y, double W, int direction) : CameraObject(){
    x = X*32;
    y = Y*32;
    w = W*32;
    dir = direction;
}

void OneWayCameraObject::modifyCamera(Camera* c, double deltaTime, double W, double H){
    double p = dir%2 == 0 ? c->getY() : c->getX();
    p += dir/2 == 0 ? (dir%2 == 0 ? H : W) : 0;
    double* dP = dir%2 == 0 ? &(c->dY) : &(c->dX);
    double lim = dir%2 == 0 ? y : x;
    int sign = dir/2 == 0 ? 1 : -1;
    printf("%f, %f\n", p*sign, (p+*dP*deltaTime)*sign);
    if (p*sign <= lim && (p+*dP*deltaTime)*sign > lim){
        *dP = (lim*sign-p)/deltaTime;
    }
}

void OneWayCameraObject::changeX(double X){
    x = X;
}

void OneWayCameraObject::changeY(double Y){
    y = Y;
}
