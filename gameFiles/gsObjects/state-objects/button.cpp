#include "button.h"

Button::Button(double X, double Y, int direction, std::string pressedValue) : Instance(X, Y, 2, 1){
    multiPress = false;
    pressedVal = pressedValue;
    maxPress = 1;
    setUp(direction);
}

Button::Button(double X, double Y, int direction, std::string pressedValue, int maxPressed) : Instance(X, Y, 2, 1){
    multiPress = (maxPressed == 1);
    maxPress = maxPressed;
    pressedVal = pressedValue;
    setUp(direction);
}

void Button::setUp(int dir){
    pressed = 0;
    pressDown = false;
    pressDir = dir;
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

void Button::update(double deltaTime, bool* keyPressed, bool* keyHeld){
    if (!multiPress) return;
    std::map<Instance *, bool>::iterator insts = collWith.begin();
    std::vector<Instance *> toRemove;
    // Remove stuff that's no longer colliding with the object.
    for (; insts != collWith.end(); insts++){
        if (!insts->second){
            toRemove.push_back(insts->first);
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

void Button::collided(Instance* o, double deltaTime){
    // Make sure the dX/dY lines up with the direction the button is.
    // Based on which direction needs to be held to press the button...
    // Top = 0, Right = 1, Bottom = 2, Left = 3
    int sign = pressDir < 2 ? -1 : 1;
    if (pressDir%2 == 0 && o->getCollDY()*sign >= 0) return;
    if (pressDir%2 == 1 && o->getCollDX()*sign >= 0) return;
    if (multiPress){
        std::map<Instance *, bool>::iterator obj = collWith.find(o);
        if (obj != collWith.end()){
            collWith[o] = true;
        } else collWith.insert({o, true});
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
    if (!multiPress) return;
    pressed += 1 % maxPress;
}
