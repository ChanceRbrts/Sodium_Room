#include "enclosedLevel.h"

EnclosedLevel::EnclosedLevel(double X, double Y, double W, double H, Level* l) : InstanceLev(X, Y, W, H){
    lev = l;
    levelUp = false;
    prevLevelUp = levelUp;
    if (W == 0) openHorizontally = true;
    else if (H == 0) openHorizontally = false;
    else {
        fprintf(stderr, "WARNING for EnclosedLevel: w or h expected to be 0");
        openHorizontally = true;
    }
    if (l->w == 0 && l->h == 0){
        l->createLevel();
    }
    trueW = openHorizontally ? l->w : l->h;
    name = "Enclosed Level";
    messWithLevel = true;
    openTime = 0;
    maxOpenTime = 1;
    open = false;
    needExtra = true;
}

void EnclosedLevel::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    lastW = openHorizontally ? w : h;
    prevLevelUp = levelUp;
    if (open && openTime < maxOpenTime){
        openTime += deltaTime;
        if (openTime > maxOpenTime){ 
            openTime = maxOpenTime;
            levelUp = true;
        }
    } else if (!open && openTime > 0){
        levelUp = false;
        openTime -= deltaTime;
        if (openTime < 0) openTime = 0;
    }
    solid = openTime > 0 && openTime < maxOpenTime;
    if (openHorizontally) w = trueW*openTime/maxOpenTime;
    else h = trueW*openTime/maxOpenTime;
    pushLevel = abs(lastW-(openHorizontally?w:h)) > 0.0001;
}

void EnclosedLevel::drawEX(GLUtil* glu){
    GLDraw* gld = glu->draw;
    // If the level's visible, don't do anything.
    if (levelUp) return;
    gld->color(lev->r, lev->g, lev->b);
    if (openTime <= 0){
        // If the enclosed level's has a width of 0, let's make it a line. (Dotted in the future?)
        gld->begin("LINES");
        gld->vertW(x, y);
        if (openHorizontally) gld->vertW(x, y+h);
        else gld->vertW(x+w, y);
        gld->end();
        return;
    }
    // Otherwise, we're going to have to draw the entire level in this...
    // Let's start with a rectangle being the background of the level.
    gld->begin("QUADS");
    gld->vertW(x,y);
    gld->vertW(x,y+h);
    gld->vertW(x+w,y+h);
    gld->vertW(x+w,y);
    gld->end();
    // Now, we need to do a translation to the corner of the screen for this.
    float transX = gld->camX-x;
    float transY = gld->camY-y;
    float scale = maxOpenTime/openTime;
    if (openHorizontally){
        gld->pushCameraMem(transX*scale, gld->camY, scale*gld->getWidth(), gld->getHeight());
    } else {
        gld->pushCameraMem(gld->camX, transY*scale, gld->getWidth(), scale*gld->getHeight());
    }
    // Now, draw the contained level!
    lev->draw(glu, nullptr);
    gld->popCameraMem();
}

void EnclosedLevel::messWithLevels(LevelList* levs, Instance* player){
    // If we have no levels to move, then we should do nothing.
    if (levs == nullptr) return;
    if (!pushLevel) return;
    for (LevelList* ll = levs; ll != nullptr; ll = ll->next){
        Level* l = ll->lev;
        // Move/split levels to make room for the new level if they're on the right/bottom.
        // For moving the level right, let's say the midpoint of the level is where we decide if we should move it.
        if (openHorizontally){
            if (l->getXOff() <= x && l->getXOff()+l->w >= x 
                && l->getYOff() <= y+h && l->getYOff()+l->h >= y){
                l->bisectLevel(true, x-l->getXOff(), w-lastW, this);
            } else if (l->getXOff()+l->w/2 >= x) l->moveRoom(w-lastW, 0, true);
        } else {
            if (l->getYOff() <= y && l->getYOff()+l->h >= y
                && l->getXOff() <= x+w && l->getXOff()+l->w >= x){
                l->bisectLevel(false, y-l->getYOff(), h-lastW, this);
            } else if (l->getYOff()+l->h/2 >= y) l->moveRoom(0, h-lastW, true);
        }
    }
    // Move the player if applicable.
    if (player != nullptr){
        if (openHorizontally && player->x > x) player->x += w-lastW;
        else if (!openHorizontally && player->y > y) player->y += h-lastW;
    }
}
