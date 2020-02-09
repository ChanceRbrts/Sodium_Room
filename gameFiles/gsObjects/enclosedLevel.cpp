#include "enclosedLevel.h"

EnclosedLevel::EnclosedLevel(double X, double Y, double W, double H, Level* l) : Instance(X, Y, W, H){
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
}

void EnclosedLevel::draw(GLDraw* gld, GLShaders* gls){
    // If the level's invisible, don't do anything.
    if (openTime > maxOpenTime || openTime < 0) return;
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
