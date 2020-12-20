#include "mothBlocks.h"

MothBlock::MothBlock(double X, double Y) : FakeSolid(X, Y){
    deleteIfRemoved = false;
}

void MothBlock::detach(){
    deleteIfRemoved = true;
}

void MothBlock::updateBlock(double move, double cX, double cY){
    remove = move < 1;
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
            MothBlock* fs = new MothBlock(i->i->x/32, i->i->y/32);
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
    double diffX = x+w/2-centerX;
    double diffY = y+h/2-centerY;
    double angle = atan2(diffY, diffX);
    dX = 500*cos(angle);
    dY = 500*sin(angle);
    double diffX2 = x+w/2+dX*deltaTime-centerX;
    double diffY2 = y+h/2+dY*deltaTime-centerY;
    if (diffX2 > 0 != diffX > 0){
        dX = (x-centerX)/deltaTime;
    }
    if (diffY2 > 0 != diffY > 0){
        dY = (y-centerY)/deltaTime;
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
        
    }
}

void MothBlocks::draw(GLDraw* gld, GLShaders* gls, int layer){
    for (int i = 0; i < fakeSolids.size(); i++){
        fakeSolids[i]->draw(gld, gls, layer);
    }
}

bool MothBlocks::messWithLevels(LevelList* levs, Level* lv, Map* map, Instance* player){

    return false;
}