#include "rain.h"
#include <math.h>

Rain::Rain(double X, double Y, double W, int mode) : Instance(X, Y, W, 0){
    loadedIn = false;
    rainMode = mode;
    startY = y;
    lastDY = 0;
    gravity = true;
    r = 0.5;
    g = 0.5;
    b = 1;
    solid = false;
    name = "Rain";
    colList.push_back("Solid");
    time = 0;
    for (int i = 0; i < W*100; i++){
        float randX = rand()*1.0/RAND_MAX;
        float startTime = rand()*5.0/RAND_MAX;
        float rRand = rand()*0.5/RAND_MAX;
        float bRand = rand()*0.5/RAND_MAX+0.5;
        for (int j = 0; j < 2; j++){
            vertices.push_back(randX);
            vertices.push_back(j);
            vertices.push_back(startTime);
            colors.push_back((mode == 1)?bRand:rRand);
            colors.push_back((mode == 2)?bRand:rRand);
            colors.push_back((mode == 0)?bRand:rRand);
        }
    }
    shaderCheck = true;
}

Rain::~Rain(){
    vertices.clear();
    colors.clear();
}

std::vector<int> Rain::initLayers(){
    layers.push_back(LAYER_NORMAL-1);
    layers.push_back(LAYER_NORMAL+1);
    return layers;
}

void Rain::initShaders(GLShaders* gls){
    if (!gls->programExists("rainShader")){
        gls->createProgram("gameFiles/shaders/rain", "", "rainShader");
    }
    if (!gls->programExists("rainPlayer")){
        gls->createProgram("gameFiles/shaders/rainPlayer", "", "rainPlayer");
    }
}

void Rain::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    loadedIn = true;
    // So collision is handled with dY... So I have to account for that.
    lastDY = dY;
    // Get our 5 second interval here.
    time = fmod(time+deltaTime, 5); 
}

void Rain::fUpdate(double deltaTime){
    if (loadedIn && (dY == 0 || time > 4)){
        gravity = false;
        dY = 0;
    }
    h = h+(y-startY);
    y = startY;
}

void Rain::collided(Instance *o, double deltaTime){
    Player* p;
    if (o->getName().compare("Player") != 0){
        return;
    }
    p = (Player *)o;
    bool fall = (rainMode == 1);
    bool up = (rainMode == 2);
    std::vector<ArcInfo> oList = o->getArcList();
    // Now, we need to get the arcs that this is affected by.
    for (int i = 0; i < arcList.size(); i++){
        ArcInfo aI = arcList[i];
        // So far, the lighter is the only thing that has this.
        // The lighter does not collide with the player, so I'll put this here for now.
        // If in the future I have another defBehavior arc, I may move this.
        if (aI.defBehavior){
            fall = (rainMode == 1);
            up = (rainMode == 2);
            break;
        }
        // Look at the player's arcs and see if they're affected by the same ID.
        bool keepGoing = false;
        for (int j = 0; j < oList.size(); j++){
            if (aI.id == oList[j].id){
                keepGoing = true;
                break;
            }
        }
        if (!keepGoing) continue;
        if (aI.r > 0.5 && aI.b < 0.5){ // Red Rain
            fall = true;
        } else if (aI.r < 0.5 && aI.b > 0.5){ // Blue Rain
            fall = false;
        } else if (aI.g > 0.5) up = true;
    }
    bool stillCheck = !p->isLocked() && ((abs(p->dX) < 0.01 && (abs(p->dY) < 0.01)) || fall);
    // The player's bounds should actually be inside the rain.
    bool inBoundsFloor = (o->y+o->h < y+h) || (o->y+o->h == y+h && up);
    bool outBoundsFloor = (o->y > y+1) || (o->y >= y && !up);
    if (o->y < y+1 && up && fall){
        o->dY = 0;
    }
    if (o->x >= x && o->x+o->w <= x+w && outBoundsFloor && inBoundsFloor && stillCheck){
        p->lockPlayer(true);
        p->hide(true);
        toAdd.push_back(new RainPlayer(p, !up));
    }
}

void Rain::draw(GLDraw* gld, GLShaders* gls, int layer){
    if (shaderCheck){
        initShaders(gls);
        shaderCheck = false;
    }
    int program = gls->bindShader("rainShader");
    // Convert stuff to window coords.
    pointDouble xy = gld->vPoint(x, y);
    // Let's also get our gravity in window coords.
    gls->addUniform(program, "x", xy.x);
    gls->addUniform(program, "y", xy.y);
    gls->addUniform(program, "w", w*2/gld->getWidth());
    gls->addUniform(program, "h", -h*2/gld->getHeight());
    // Hard coded right now; I wonder what "fun" problems this will lead to in the future! :|
    gls->addUniform(program, "termV", termY);
    // gls->addUniform(program, "termV", -termY*2/gld->getHeight());
    gls->addUniform(program, "unitX", 2/gld->getWidth());
    gls->addUniform(program, "unitY", -2/gld->getHeight());
    gls->addUniform(program, "time", time);
    gld->drawArray(&vertices[0], &colors[0], nullptr, vertices.size()/3, 3, 3, "LINES");
    gls->unbindShader();
    /*
    // For right now, this is a simple transparent rectangle so I can test things.
    gld->color(r,g,b,0.5);
    // Draws a rectangle with colors r, g, and b.
    gld->begin("QUADS");
    gld->vertW(x,y);
    gld->vertW(x,y+h);
    gld->vertW(x+w,y+h);
    gld->vertW(x+w,y);
    gld->end();
    */
}

// Rain Player

RainPlayer::RainPlayer(Player* pl, bool gDown) : Instance(pl->x/32, pl->y/32, pl->w/32, pl->h/32){
    p = pl;
    backTogether = false;
    gravity = true;
    time = 0;
    timeApart = 0;
    maxTimeApart = 0.3;
    maxTime = 999;
    if (!gDown) termY = -termY;
    dX = 0;
    dY = 0;
    solid = false;
    name = "RainPlayer";
    colList.push_back("Solid");
    for (int i = 0; i < w; i++){
        float offset = rand()*maxTimeApart/RAND_MAX;
        for (int j = 0; j < 2; j++){
            vertices.push_back(i);
            vertices.push_back(j==0?0:h);
            vertices.push_back(offset);
            colors.push_back(p->getR());
            colors.push_back(p->getG());
            colors.push_back(p->getB());
            // texs.push_back(i*1.0/w);
            // texs.push_back();
        }
    }
}

RainPlayer::~RainPlayer(){
    vertices.clear();
    colors.clear();
    // texs.clear();
}

std::vector<int> RainPlayer::initLayers(){
    layers.push_back(LAYER_NORMAL-1);
    layers.push_back(LAYER_NORMAL+1);
    return layers;
}

void RainPlayer::fUpdate(double deltaTime){
    // This instance was stopped.
    if (dY == 0 && time > 0 && !backTogether){
        backTogether = true;
        maxTime = time;
    }
    // Have the shader draw the lines kind of apart here.
    if (backTogether){
        timeApart += deltaTime;
        if (timeApart > maxTimeApart){
            timeApart = maxTimeApart;
            p->lockPlayer(false);
            p->hide(false);
            remove = true;
        }
    }
    time += deltaTime;
    // Move the player to the hitbox of the instance.
    p->x = x;
    p->y = y;
    p->dX = 0;
    p->dY = 0;
}

void RainPlayer::draw(GLDraw* gld, GLShaders* gls, int layer){
    int program = gls->bindShader("rainPlayer");
    pointDouble xy = gld->vPoint(x, y);
    gls->addUniform(program, "x", xy.x);
    gls->addUniform(program, "y", xy.y);
    // Hard coded right now; I wonder what "fun" problems this will lead to in the future! :|
    gls->addUniform(program, "termV", abs(termY));
    gls->addUniform(program, "unitX", 2/gld->getWidth());
    gls->addUniform(program, "unitY", -2/gld->getHeight());
    gls->addUniform(program, "gravityDown", (termY > 0)? 1:0);
    gls->addUniform(program, "time", time);
    gls->addUniform(program, "maxTime", maxTime);
    gld->drawArray(&vertices[0], &colors[0], nullptr, vertices.size()/3, 3, 3, "LINES");
    gls->unbindShader();
}
