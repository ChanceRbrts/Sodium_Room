#include "mothBlocks.h"

MothBlock::MothBlock(double X, double Y, double cX, double cY) : FakeSolid(cX+X, cY+Y){
    deleteIfRemoved = false;
    startX = X*32;
    startY = Y*32;
}

void MothBlock::detach(){
    deleteIfRemoved = true;
}

void MothBlock::updateBlock(double move, double cX, double cY){
    remove = move < 1;
    // printf("%f, %f, %f, %f, %f\n", cX, cY, cX+startX*move, cY+startY*move, move);
    x = cX+startX*move;
    y = cY+startY*move;
    // Make it so the blocks are split apart if they are moving.
    if (move < 1){
        float rad = atan2(pY-y, pX-x);
        pX += 128*(1-move)*cos(rad);
        pY += 128*(1-move)*sin(rad);
    }
}

MothBlocks::MothBlocks(double X, double Y, std::string filename) : InstanceLev(X, Y, 1, 1){
    // Initialize our level.
    Level* l = new Level();
    l->filePath = filename;
    l->createLevel();
    double wid = l->w;
    double hei = l->h;
    // Build the fake solid vector based off the solids.
    if (l->insts != nullptr){
        for (Instances* i = l->insts; i != nullptr; i = i->next){
            MothBlock* fs = new MothBlock(i->i->x/32, i->i->y/32, x/32, y/32);
            if (i->i->texID() != 0){
                fs->changeTexture(i->i->texID(), true);
            }
            fakeSolids.push_back(fs);
        }
    }
    // Remove the level that we made to create the fake solids.
    delete l;
    w = wid;
    h = hei;
    blocksPlacedDown = false;
    move = 1;
    maxMove = 1;
    solid = false;
    canPlaceBlocks = true;
    messWithLevel = true;
}

MothBlocks::~MothBlocks(){
    // If the blocks have been placed down, then 
    if (blocksPlacedDown){
        // If the blocks have been placed down in the level, detach them from this object.
        for (int i = 0; i < fakeSolids.size(); i++){
            fakeSolids[i]->detach();
        }
    } else {
        // Otherwise, delete the fake solids attached to this object.
        for (int i = 0; i < fakeSolids.size(); i++){
            delete fakeSolids[i];
        }
    }
    fakeSolids.clear();
}

void MothBlocks::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    if (canPlaceBlocks && move >= maxMove && !blocksPlacedDown){
        // Place the blocks down!
        for (int i = 0; i < fakeSolids.size(); i++){
            toAdd.push_back(fakeSolids[i]);
        }
        blocksPlacedDown = true;
    }
    int arcToFollow = -1;
    double maxBright = 0;
    for (int i = 0; i < arcList.size(); i++){
        if (arcList[i].defBehavior && maxBright < 3.7){
            arcToFollow = i;
            maxBright = 3.7;
        } else if (arcList[i].r+arcList[i].g+arcList[i].b > maxBright){
            arcToFollow = i;
            maxBright = arcList[i].r+arcList[i].g+arcList[i].b;
        }
    }
    if (arcToFollow == -1){
        return;
    }
    double centerX = arcList[arcToFollow].cX;
    double centerY = arcList[arcToFollow].cY;
    // Move the object towards the center of mass of the arc!
    double diffX = centerX-(x+w/2);
    double diffY = centerY-(y+h/2);
    double angle = atan2(diffY, diffX);
    if (abs(diffX) < 0.001 && abs(diffY) < 0.001){
        dX = 0;
        dY = 0;
    } else {
        dX = 500*cos(angle);
        dY = 500*sin(angle);
        double diffX2 = centerX-(x+w/2+dX*deltaTime);
        double diffY2 = centerY-(y+h/2+dY*deltaTime);
        if (diffX2 > 0 != diffX > 0){
            dX = (x-centerX)/deltaTime;
        }
        if (diffY2 > 0 != diffY > 0){
            dY = (y-centerY)/deltaTime;
        }
    }
    bool onLighter = arcToFollow > -1 && arcList[arcToFollow].defBehavior;
    // Update the move variable based on the dX and dY of the arc.
    if (abs(dX) < 0.001 && abs(dY) < 0.001 && !onLighter && move < maxMove){
        move += deltaTime;
        if (move > maxMove) move = maxMove;
    } else if ((abs(dX) > 0.001 || abs(dY) > 0.001 || onLighter) && move > 0){
        move -= 4*deltaTime;
        if (move < 0) move = 0;
    }
    // Update the moth blocks based on the move variable.
    for (int i = 0; i < fakeSolids.size(); i++){
        if (!blocksPlacedDown){
            fakeSolids[i]->update(deltaTime, keyPressed, keyHeld, player);
        }
        fakeSolids[i]->updateBlock(move/maxMove, x+dX*deltaTime+w/2, y+dY*deltaTime+h/2);
    }
    if (move < maxMove){
        blocksPlacedDown = false;
    }
    canPlaceBlocks = true;
}

void MothBlocks::draw(GLDraw* gld, GLShaders* gls, int layer){
    if (blocksPlacedDown) return;
    for (int i = 0; i < fakeSolids.size(); i++){
        fakeSolids[i]->draw(gld, gls, layer);
    }
}

bool MothBlocks::messWithLevels(LevelList* levs, Level* lv, Map* map, Instance* player){
    if (arcList.size() > 0) return false;
    double minDiff = -1;
    double xTo = 0;
    double yTo = 0;
    PlayerAbility* pA = ((Player *)player)->getAbility();
    if (pA != nullptr){
        ArcInfo pI = pA->getArc()->getInfo(0);
        if (pI.a > 0){
            // Go towards the player arc to set up.
            double diffX = x+w/2-pI.cX;
            double diffY = y+h/2-pI.cY;
            minDiff = sqrt(pow(diffX, 2)+pow(diffY, 2));
            xTo = pI.cX-w/2;
            yTo = pI.cY-h/2;
        }
    }
    // Go to the closest arc in the level.
    for (int i = 0; i < lv->arcs.size(); i++){
        ArcInfo a = lv->arcs[i]->getInfo(0);
        if (lv->arcs[i]->getR() <= 0 || a.a <= 0) continue;
        double diffX = x+w/2-a.cX;
        double diffY = y+h/2-a.cY;
        double diff = sqrt(pow(diffX, 2)+pow(diffY, 2));
        if (minDiff < 0 || diff < minDiff){
            minDiff = diff;
            xTo = a.cX-w/2;
            yTo = a.cY-h/2;
        }
    }
    if (minDiff < 0 || minDiff > 640){
        dX = 0;
        dY = 0;
        return false;
    }
    // Get the dX and dY based off of the closest distance.
    double diffX = xTo-x;
    double diffY = yTo-y;
    double rad = atan2(diffY, diffX);
    dX = 500*cos(rad);
    dY = 500*sin(rad);
    return false;
}

void MothBlocks::collided(Instance* o, double deltaTime){
    // Make sure the object is solid and is not a piece of ground.
    if (!o->isSolid(name) || o->isImmovable()) return;
    // Do a quick collision check to see if the object is obstructing the blocks from appearing.
    for (int i = 0; i < fakeSolids.size(); i++){
        Instance* fS = fakeSolids[i];
        if (fS->x+fS->w < o->x+o->dX*deltaTime && fS->x > o->x+o->w+o->dX*deltaTime &&
            fS->y+fS->h < o->y+o->dY*deltaTime && fS->y > o->y+o->h+o->dY*deltaTime){
            blocksPlacedDown = false;
        }
    }
}