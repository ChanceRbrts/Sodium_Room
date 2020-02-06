#include "../glUtil.h"
#include "sdl.h"

// Note to Self: Static Variables need to be Initialized Here
bool GLControls::keyPressed[CON_LEN] = 
               {false,false,false,false,false,false,false,false,false,false};
bool GLControls::keyHeld[CON_LEN] = 
               {false,false,false,false,false,false,false,false,false,false};
char GLControls::keys[CON_LEN] = {0,0,0,0,0,0,0,0,0,0};
int GLControls::keysS[CON_LEN] = {0,0,0,0,0,0,0,0,0,0};
int GLControls::mouseX = 0;
int GLControls::mouseY = 0;
int GLControls::mousePressed = -1;
int GLControls::mLeft = SDL_BUTTON_LEFT;
int GLControls::mCenter = SDL_BUTTON_MIDDLE;
int GLControls::mRight = SDL_BUTTON_RIGHT;

GLControls::GLControls(void* eInfo){
   keys[BUTTON_LEFT] = 'A';
   keys[BUTTON_RIGHT] = 'D';
   keys[BUTTON_UP] = 'W';
   keys[BUTTON_DOWN] = 'S';
   keys[BUTTON_A] = 'X';
   keys[BUTTON_B] = 'Z';
   keysS[BUTTON_END] = SDLK_ESCAPE;
   keysS[BUTTON_LEFT] = SDLK_LEFT;
   keysS[BUTTON_RIGHT] = SDLK_RIGHT;
   keysS[BUTTON_UP] = SDLK_UP;
   keysS[BUTTON_DOWN] = SDLK_DOWN;
   keysS[BUTTON_START] = SDLK_RETURN;
   keysS[BUTTON_SELECT] = SDLK_SPACE;
   extraInfo = eInfo;
}

void GLControls::keyDown(unsigned char ch, int x, int y){
   for (int i = 0; i < CON_LEN; i++){
      if (keys[i] != 0 && keys[i] == ch){
         if (!keyHeld[i]) keyPressed[i] = true;
         keyHeld[i] = true;
      }
   }
}

void GLControls::keyUp(unsigned char ch, int x, int y){
   for (int i = 0; i < CON_LEN; i++){
      if (keys[i] != 0 && keys[i] == ch){
         keyHeld[i] = false;
      }
   }
}

void GLControls::specialKey(int key, int x, int y){
   for (int i = 0; i < CON_LEN; i++){
      if (keysS[i] != 0 && keysS[i] == key){
         if (!keyHeld[i]) keyPressed[i] = true;
         keyHeld[i] = true;
      }
   }
}
      
void GLControls::specialKeyUp(int key, int x, int y){
   for (int i = 0; i < CON_LEN; i++){
      if (keysS[i] != 0 && keysS[i] == key){
         keyHeld[i] = false;
      }
   }
}

void GLControls::mouseFunc(int button, int state, int x, int y){}
void GLControls::mouseMotion(int x, int y){}
void GLControls::mousePassMotion(int x, int y){}

void GLControls::controlLoop(){
   SDL_Event e;
   while (SDL_PollEvent(&e)){
      if (e.type == SDL_KEYDOWN){
         std::string keyCode = std::string(SDL_GetKeyName(e.key.keysym.sym));
         if (keyCode.length() == 1) keyDown(keyCode[0], 0, 0);
         else specialKey(e.key.keysym.sym, 0, 0);
      } else if (e.type == SDL_KEYUP){
         std::string keyCode = std::string(SDL_GetKeyName(e.key.keysym.sym));
         if (keyCode.length() == 1) keyUp(keyCode[0], 0, 0);
         else specialKeyUp(e.key.keysym.sym, 0, 0);
      } else if (e.type == SDL_MOUSEBUTTONDOWN){
         // I'll implement this if I need to.
      } else if (e.type == SDL_MOUSEBUTTONUP){
         // I'll implement this if I need to.
      }
   }
}

void GLControls::resetControls(){
   for (int i = 0; i < CON_LEN; i++){
      keyPressed[i] = false;
   }
   mousePressed = -1;
}
