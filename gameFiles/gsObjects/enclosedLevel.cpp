#include "enclosedLevel.h"

EnclosedLevel::EnclosedLevel(double X, double Y, double W, double H, Level* l) : InstanceLev(X, Y, W, H){
    lev = l;
    levelUp = false;
    prevLevelUp = levelUp;
    if (openHorizontally){
        trueW = w;
        w = 0;
    } else {
        trueW = h;
        h = 0;
    }
    name = "Enclosed Level";
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
    if (openHorizontally) w = trueW*openTime/maxOpenTime;
    else h = trueW*openTime/maxOpenTime;
    messWithLevel = abs(lastW-(openHorizontally?w:h)) < 0.0001;
}

void EnclosedLevel::draw(GLDraw* gld, GLShaders* gls){
    // If the level's invisible, don't do anything.
    if (openTime > maxOpenTime || openTime <= 0) return;
    // Otherwise, we're going to have to draw the entire level in this...
    // Let's start with a rectangle being the background of the level.
    gld->color(lev->r, lev->g, lev->b);
    gld->begin("QUADS");
    gld->vertW(x,y);
    gld->vertW(x,y+h);
    gld->vertW(x+w,y+h);
    gld->vertW(x+w,y);
    gld->end();
}

void EnclosedLevel::messWithLevels(LevelList* levs, Instance* player){
    // If we have no levels to move, then we should do nothing.
    if (levs == nullptr) return;
    for (LevelList* ll = levs; ll != nullptr; ll = ll->next){
        Level* l = ll->lev;
        // Move/split levels to make room for the new level if they're on the right/bottom.
        // For moving the level right, let's say the midpoint of the level is where we want to say we want to move it.
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
        if (openHorizontally && player->x > x) x += w-lastW;
        else if (!openHorizontally && player->y > y) y += h-lastW;
    }
}
