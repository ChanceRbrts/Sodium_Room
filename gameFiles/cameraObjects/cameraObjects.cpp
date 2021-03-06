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
    closeH = 0;
    openH = 0;
    snap = true;
}

OneWayCameraObject::OneWayCameraObject(double X, double Y, double W, double removeH, 
                                       double addH, int direction, bool snapback) : CameraObject(){
    x = X*32;
    y = Y*32;
    w = W*32;
    prevWork = true;
    work = true;
    dir = direction;
    closeH = removeH;
    openH = addH;
    snap = snapback;
}

void OneWayCameraObject::modifyCamera(Camera* c, double deltaTime, double W, double H){
    if (!work) return;
    double p = dir%2 == 0 ? c->getY() : c->getX();
    p += dir/2 == 0 ? (dir%2 == 0 ? H : W) : 0;
    double q = dir%2 == 0 ? c->getX() : c->getY();
    double myQ = dir%2 == 0 ? x : y;
    // If the one way camera object can't possibly be on screen, don't do other checks.
    if (myQ+w < q || myQ > q+(dir%2 == 0 ? W : H)) return;
    double* dP = dir%2 == 0 ? &(c->dY) : &(c->dX);
    double lim = dir%2 == 0 ? y : x;
    int sign = dir/2 == 0 ? 1 : -1;
    if (p*sign <= lim*sign && (p+*dP*deltaTime)*sign > lim*sign){
        *dP = (lim-p)/deltaTime;
    }
}

pointDouble OneWayCameraObject::interactWithPlayer(double cX, double cY, double W, double H, Instance* i, double deltaTime){
    prevWork = work;
    double p = dir%2 == 0 ? i->y : i->x;
    double offset = work ? closeH : openH;
    p += dir/2 == 0 ? -offset : offset;
    double dP = dir%2 == 0 ? i->dY : i->dX;
    int sign = dir/2 == 0 ? 1 : -1;
    double lim = dir%2 == 0 ? y : x;
    work = (p+dP*deltaTime)*sign < lim*sign;
    if (!work || !snap) return (pointDouble){cX, cY, 0};
    double q = dir%2 == 0 ? cX : cY;
    double myQ = dir%2 == 0 ? x : y;
    // If the one way camera object can't possibly be on screen, don't do other checks.
    if (myQ+w < q || myQ > q+(dir%2 == 0 ? W : H)) return (pointDouble){cX, cY, 0};
    // If the camera still displays the target and there's snapback, set a target.
    double cP = dir%2 == 0 ? cY : cX;
    cP += sign > 0 ? (dir%2 == 0 ? H : W) : 0;
    // If the camera object is no longer visible, don't do anything.
    if (cP*sign > lim*sign){
        double camTargetX = dir%2 == 0 ? cX : lim-(sign > 0 ? W : 0);
        double camTargetY = dir%2 == 0 ? lim-(sign > 0 ? H : 0) : cY;
        return {camTargetX, camTargetY, 0};
    }
    return (pointDouble){cX, cY, 0};
}

void OneWayCameraObject::bisectObject(bool horizontal, float splitLocation, float offset){
    double* p = horizontal ? &x : &y;
    if (*p > splitLocation){
        *p += offset;
        if (*p < splitLocation) *p = splitLocation;
    }
    if (horizontal != dir%2 && *p < splitLocation && *p+w > splitLocation){
        // In this case, w needs to change.
        // Either that, or the object will need to bisect as well.
        w += offset;
        if (*p+w < splitLocation) w = splitLocation-*p;
    }
}

void OneWayCameraObject::setPosition(double X, double Y, bool relative){
    changeX(X+(relative? x : 0));
    changeY(Y+(relative? y : 0));
}

void OneWayCameraObject::changeX(double X){
    x = X;
}

void OneWayCameraObject::changeY(double Y){
    y = Y;
}

void OneWayCameraObject::setPosValues(OneWayCameraObject* o){
    x = o->x;
    y = o->y;
    w = o->w;
}
