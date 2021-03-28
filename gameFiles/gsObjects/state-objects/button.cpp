#include "button.h"

Button::Button(double X, double Y, int direction, std::string pressedValue, bool updateMe) : Instance(X, Y, 2, 1){
    multiPress = false;
    pressedVal = pressedValue;
    maxPress = 1;
    setUp(direction);
    updateState = updateMe;
}

Button::Button(double X, double Y, int direction, std::string pressedValue, int maxPressed, bool updateMe) : Instance(X, Y, 2, 1){
    multiPress = (maxPressed > 0);
    maxPress = maxPressed;
    pressedVal = pressedValue;
    setUp(direction);
    updateState = updateMe;
}


void Button::setUp(int dir){
    pressed = 0;
    pressDown = false;
    prevPress = false;
    immovable = true;
    pressDir = dir;
    pEpsilon = 0.15;
    name = "Button";
    // Retrieve the game state from the button (if it exists)
    int value = GameState::getType(pressedVal);
    int pressVal = GameState::getType(pressedVal+"_pressed");
    if (value == SAV_BOOL){
        pressed = GameState::getSaveB(pressedVal) ? 1 : 0;
    } else if (value == SAV_INT){
        pressed = GameState::getSaveI(pressedVal);
    }
    if (pressVal == SAV_BOOL){
        pressDown = GameState::getSaveB(pressedVal+"_pressed");
    }
    // Based on which direction needs to be held to press the button...
    // Top = 0, Right = 1, Bottom = 2, Left = 3
    w = dir%2 == 0 ? 64 : 16;
    h = dir%2 == 0 ? 16 : 64;
    // A bit of redundancy here, fix if dimensions are correct.
    x += (dir == 1) ? 16 : 0;
    y += (dir == 0) ? 16 : 0;
    // x += dir%2 == 0 ? 0 : (dir == 1 ? 16 : 0);
    // y += dir%2 == 0 ? (dir == 0 ? 16 : 0) : 0;
}

void Button::unpushCheck(double deltaTime){
    if (!multiPress && pressed > 0) return;
    std::map<Instance *, double>::iterator insts = collWith.begin();
    std::vector<Instance *> toRemove;
    // Remove stuff that's no longer colliding with the object.
    for (; insts != collWith.end(); insts++){
        Instance* o = insts->first;
        collWith[o] -= deltaTime;
        if (collWith[o] < 0){
            toRemove.push_back(o);
        }
    }
    for (int i = 0; i < toRemove.size(); i++){
        collWith.erase(toRemove[i]);
    }
    if (collWith.begin() == collWith.end()){
        pressDown = false;
        GameState::setSaveB(pressedVal+"_pressed", false);
    }
}

void Button::changePress(double deltaTime){
    double* toChange = pressDir%2 == 0 ? &h : &w;
    double* adjustX = pressDir%2 == 0 ? &dY : &dX;
    bool toAdjust = pressDir < 2;
    *toChange = pressDown ? 8 : 16;
    if (toAdjust){
        *adjustX += (pressDown ? 8 : -8)/deltaTime;
    }
}

void Button::stateChange(){
    if (multiPress) pressed = GameState::getSaveI(pressedVal);
    else pressed = GameState::getSaveB(pressedVal) ? 1 : 0;
}

void Button::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    dX = 0;
    dY = 0;
    unpushCheck(deltaTime);
    // If there's state to update, do it here.
    if (updateState) stateChange();
    if (prevPress != pressDown){
        changePress(deltaTime);
    }
    prevPress = pressDown;
}

void Button::collided(Instance* o, double deltaTime){
    // Make sure the dX/dY lines up with the direction the button is.
    // Based on which direction needs to be held to press the button...
    // Top = 0, Right = 1, Bottom = 2, Left = 3
    int sign = pressDir < 2 ? -1 : 1;
    if (pressDir%2 == 0 && (o->getCollDY()*sign >= 0 || o->x >= x+w || o->x+o->w <= x)) return;
    if (pressDir%2 == 1 && (o->getCollDX()*sign >= 0 || o->y >= y+h || o->y+o->h <= y)) return;
    if (multiPress){
        std::map<Instance *, double>::iterator obj = collWith.find(o);
        if (obj != collWith.end()){
            collWith[o] = pEpsilon;
        } else collWith.insert({o, pEpsilon});
    }
    // Make sure the button hasn't already been pressed.
    if ((pressed && !multiPress) || pressDown) return;
    // Finally, update the game state with what the button directs it to.
    pressDown = true;
    changeState();
    if (multiPress) GameState::setSaveI(pressedVal, pressed);
    else GameState::setSaveB(pressedVal, pressed != 0); 
    GameState::setSaveB(pressedVal+"_pressed", true);
}

void Button::makePermanent(){
    GameState::makePermament(pressedVal);
    GameState::makePermament(pressedVal+"_pressed");
}

void Button::changeState(){
    if (!multiPress) pressed = 1;
    else pressed = (pressed+1) % maxPress;
}
