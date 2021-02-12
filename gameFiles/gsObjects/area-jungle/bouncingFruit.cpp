#include "bouncingFruit.h"

BouncingFruit::BouncingFruit(double X, double Y, bool goingRight) : Instance(X, Y, 1, 1){
    r = 0.92;
    g = 0.63;
    b = 0.2;
    gravity = true;
    stopped = false;
    prevFaceBack = false;
    facingRight = goingRight;
    speed = 512;
    dX = speed*(facingRight?1:-1);
    speedup = 0.5;
    maxSpeedup = 0.5;
    waitTime = 0;
    maxWaitTime = 0.125;
    name = "Bouncing Fruit";
}

void BouncingFruit::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    double arcR = 0;
    double arcG = 0;
    double arcB = 0;
    bool hasArc = arcList.size() > 0;
    bool defBehavior = false;
    for (int i = 0; i < arcList.size(); i++){
        arcR += arcList[i].r;
        arcG += arcList[i].g;
        arcB += arcList[i].b;
        if (arcList[i].defBehavior){
            defBehavior = true;
            continue;
        }
    }
    if (!defBehavior && hasArc){
        arcR /= arcList.size();
        arcG /= arcList.size();
        arcB /= arcList.size();
    }
    bool faceBack = !defBehavior && arcR < 0.5 && arcG > 0.5 && arcB < 0.5;
    if (dX == 0){
        facingRight = !facingRight;
        speedup = 0;
    }
    if (onGround){
        waitTime += deltaTime;
        if (waitTime > maxWaitTime){
            waitTime = 0;
            dY = -400;
        }
    }
    if (waitTime <= 0 && !faceBack && speedup < maxSpeedup){
        speedup += deltaTime;
        if (speedup > maxSpeedup) speedup = maxSpeedup;
    } else if (waitTime <= 0 && faceBack && speedup > -maxSpeedup){
        speedup -= deltaTime*6;
        if (speedup < -maxSpeedup) speedup = -maxSpeedup;
    } else if (prevFaceBack && !faceBack && speedup < maxSpeedup){
        speedup = -speedup;
        facingRight = !facingRight;
    }
    dX = speed*speedup*(facingRight?1:-1)*(onGround?0.45:1);
    prevFaceBack = faceBack;
}

void BouncingFruit::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Soil") != 0 || remove) return;
    /// Plant the fruit, creating a flower.
    if (x >= o->x && x+w <= o->x+o->w && y < o->y){
        toAdd.push_back(new GiantFlower(x/32-0.5, (o->y/32)-14));
        remove = true;
    }
}

GiantFlower::GiantFlower(double X, double Y) : Instance(X, Y, 2, 14){
    solid = false;
    immovable = true;
    r = 0.1;
    g = 0.8;
    b = 0.1;
    makeLeaf = 0.5;
    name = "GiantFlower";
}

std::vector<int> GiantFlower::initLayers(){
    std::vector<int> layers;
    layers.push_back(LAYER_NORMAL-1);
    return layers;
}

void GiantFlower::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    if (makeLeaf <= 0) return;
    float pMakeLeaf = makeLeaf;
    makeLeaf -= deltaTime;
    if (pMakeLeaf > 0.15 && makeLeaf <= 0.15){
        toAdd.push_back(new Leaf(x/32+1.5, y/32+6, true));
    }
    if (makeLeaf <= 0){
        makeLeaf = 0;
        toAdd.push_back(new Leaf(x/32+0.5, y/32+4, false));
    }
}

Leaf::Leaf(double X, double Y, bool growRight) : Instance(X, Y, 0, 1){
    leafGrow = 0;
    immovable = true;
    maxLeafGrow = 0.25;
    gRight = growRight;
    semiColl[COLL_BOTTOM] = false;
    semiColl[COLL_LEFT] = false;
    semiColl[COLL_RIGHT] = false;
    name = "Leaf";
    r = 0.3;
    g = 1;
    b = 0.3;
}

std::vector<int> Leaf::initLayers(){
    std::vector<int> layers;
    layers.push_back(LAYER_NORMAL-1);
    return layers;
}

void Leaf::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    if (leafGrow >= maxLeafGrow) return;
    double dTime = deltaTime;
    leafGrow += deltaTime;
    if (leafGrow > maxLeafGrow){
        dTime -= (leafGrow-maxLeafGrow);
        leafGrow = maxLeafGrow;
    }
    w += 96*dTime/maxLeafGrow;
    if (!gRight) x -= 96*dTime/maxLeafGrow;
}

Soil::Soil(double X, double Y, double W) : Instance(X, Y, W, 1){
    name = "Soil";
    immovable = true;
    r = 0.35;
    g = 0.23;
    b = 0.09;
}
