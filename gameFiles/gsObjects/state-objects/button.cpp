#include "button.h"

Button::Button(double X, double Y, int direction, std::string pressedValue) : Instance(X, Y, 1, 1){
    multiPress = false;
    pressedVal = pressedValue;
    setUp(direction);
}

Button::Button(double X, double Y, int direction, std::string pressedValue, bool multiPressed) : Instance(X, Y, 1, 1){
    multiPress = multiPressed;
    pressedVal = pressedValue;
    setUp(direction);
}

void Button::setUp(int dir){
    pressed = 0;
    pressDown = false;
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
    w = dir%2 == 0 ? 32 : 8;
    h = dir%2 == 0 ? 8 : 32;
    x += dir%2 == 0 ? 16 : (dir == 1 ? 24 : 0);
    y += dir%2 == 0 ? (dir == 0 ? 24 : 0) : 16;
}

void Button::update(double deltaTime, bool* keyPressed, bool* keyHeld){

}

void Button::collided(Instance* o, double deltaTime){
    // Make sure the dX/dY lines up with the direction the button is.

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
