#include "glut.h"
#include "../glUtil.h"

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
int GLControls::mLeft = GLUT_LEFT_BUTTON;
int GLControls::mCenter = GLUT_MIDDLE_BUTTON;
int GLControls::mRight = GLUT_RIGHT_BUTTON;


GLControls::GLControls(void* eInfo){
   keys[LEFT] = 'a';
   keys[RIGHT] = 'd';
   keys[UP] = 'w';
   keys[DOWN] = 's';
   keys[A] = 'x';
   keys[B] = 'z';
   keys[START] = '\n';
   keys[SELECT] = ' ';
   keys[END] = 27;
   keysS[LEFT] = GLUT_KEY_LEFT;
   keysS[RIGHT] = GLUT_KEY_RIGHT;
   keysS[UP] = GLUT_KEY_UP;
   keysS[DOWN] = GLUT_KEY_DOWN;
}

void GLControls::controlLoop(){}

void GLControls::keyDown(unsigned char ch, int x, int y){
   // Make sure caps doesn't matter.
   if (ch >= 'A' && ch <= 'Z'){
      ch += 'a'-'A';
   }
   for (int i = 0; i < CON_LEN; i++){
      if (keys[i] != 0 && keys[i] == ch){
         if (!keyHeld[i]) keyPressed[i] = true;
         keyHeld[i] = true;
      }
   }
}

void GLControls::keyUp(unsigned char ch, int x, int y){
   // Make sure caps doesn't matter.
   if (ch >= 'A' && ch <= 'Z'){
      ch += 'a'-'A';
   }
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

void GLControls::mouseFunc(int button, int state, int x, int y){
   if (state == GLUT_DOWN)
      mousePressed = button;
   mouseX = x;
   mouseY = y;
}

void GLControls::mouseMotion(int x, int y){
   mouseX = x;
   mouseY = y;
}

void GLControls::mousePassMotion(int x, int y){
   mouseX = x;
   mouseY = y;
}

void GLControls::resetControls(){
   for (int i = 0; i < CON_LEN; i++){
      keyPressed[i] = false;
   }
   mousePressed = -1;
}
