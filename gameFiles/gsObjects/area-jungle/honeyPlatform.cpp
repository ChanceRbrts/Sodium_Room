#include "honeyPlatform.h"

HoneyPlatform::HoneyPlatform(double X, double Y, double W, bool horizontal) : Instance(X, Y, 1, 1){
    w = horizontal ? W*32 : 32;
    h = horizontal ? 32 : W*32;
    // I'll use f0be1e for a honey color.
    // Sticky when walking, not so sticky when climbing, affects jumping quite a bit.
    r = 240/255.0;
    g = 190/255.0;
    b = 30/255.0;
    colorSwapTime = 1.0;
    solid = false;
    stuckToWall = true;
    changedColor = false;
    name = "Honey Platform";
}

double HoneyPlatform::moveValueTo(double* vMove, double vTo, double deltaTime){
    // Move vMove closer to vTo at velocity 1.0/colorSwapTime colors/sec;
    double vM = *vMove;
    if (abs(vTo-vM) <= 0.01) return vM;
    changedColor = true;
    if (vM > vTo){
        *vMove -= 1.0/colorSwapTime*deltaTime;
        if (*vMove < vTo) *vMove = vM;
        return *vMove;
    }
    // Otherwise, we are guaranteed to have vM < vTo...
    *vMove += 1.0/colorSwapTime*deltaTime;
    if (*vMove > vTo) *vMove = vTo;
    return *vMove;
}

void HoneyPlatform::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    changedColor = false;
    // Check the arcs to see what needs to be changed here.
    double goalColorR = 0;
    double goalColorG = 0;
    double goalColorB = 0;
    // Get the average r, g, and b values shining on the platform.
    for (int i = 0; i < arcList.size(); i++){
        goalColorR += arcList[i].r;
        goalColorG += arcList[i].g;
        goalColorB += arcList[i].b;
    }
    if (arcList.size() > 0){
        goalColorR /= arcList.size();
        goalColorG /= arcList.size();
        goalColorB /= arcList.size();
        // Now that the goal color is found, move our platform to that goal color.
        moveValueTo(&r, goalColorR, deltaTime);
        moveValueTo(&g, goalColorG, deltaTime);
        moveValueTo(&b, goalColorB, deltaTime);
    }
    // Iterate through the instances that we have collided with to find the ones that we haven't this frame.
    std::map<Instance *, bool>::iterator insts = collidedInstances.begin();
    std::vector<Instance *> toRemove;
    for (; insts != collidedInstances.end(); insts++){
        bool removed = false;
        if (!insts->second){
            // We have not collided with this instance at this point, bring stuff back to normal!
            insts->first->changeDVModifier(true, 1, 0, true);
            insts->first->changeDVModifier(false, 1, 0, true);
            toRemove.push_back(insts->first);
            removed = true;
        }
        // See if our player is jumping.
        if (insts->first->getName().compare("Player") == 0){
            Player* p = (Player *)(insts->first);
            if (p->isJumping()){
                if (!removed){
                    p->changeDVModifier(true, 1, 0, true);
                    p->changeDVModifier(false, 1, 0, true);
                    toRemove.push_back(insts->first);
                    removed = true;
                }
                double jumpMul = 0.25+1.5*(1.0-g);
                p->changeJumpMultiplier(jumpMul);
                p->dY = -340*jumpMul;
            }
        }
        collidedInstances[insts->first] = false;
    }
    for (int i = 0; i < toRemove.size(); i++){
        collidedInstances.erase(toRemove[i]);
    }
}

/*
void HoneyPlatform::draw(GLDraw* gld, GLShaders* gls){

}
*/

void HoneyPlatform::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Solid") == 0) return;
    // R -> Horizontal Friction, G -> Propelling Power, B -> Vertical Friction
    std::map<Instance *, bool>::iterator obj = collidedInstances.find(o);
    if (changedColor || obj == collidedInstances.end()){
        o->changeDVModifier(true, 1-(0.7*r), 0.5, false);
        o->changeDVModifier(false, 1-(0.7*b), 0.5, false);
    }
    if (obj == collidedInstances.end()){
        collidedInstances.insert({o, true});
    } else collidedInstances[o] = true;
}
