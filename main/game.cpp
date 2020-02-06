#include "config.h"
#include "../glutils/glUtil.h"
#include "../gameFiles/gameLogic.h"

GLUtil* glu;
GameLogic* gLog;

double curTime = 0;
bool displ = true;

/**
 * The main game loop.
 * Calculates deltaTime and gives gl a reason to redisplay.
 **/
void idle(){
   double newTime = glu->getTime()/1000.0;
   if (curTime != 0){
      float deltaTime = newTime-curTime;
      gLog->update(deltaTime, glu);
      glu->redisplay();
      displ = true;
   }
   curTime = newTime;
}

/**
 * The main drawing loop.
 * On OS X, the drawing loop runs twice when the update loop runs once.
 * This destroys the frame rate, making it run with noticeable jump on OS X.
 * As such, I've made sure that it only runs if update is going.
 * If this breaks on Windows, let me know, and I'll run some compiler flags.
 */
void draw(){
   if (displ){
      glu->draw->start();
      gLog->draw(glu);
      glu->draw->finish();
   }
   displ = false;
}

/**
 * Sets everything up for use and initializes OpenGL stuff.
 */
int main(int argv, char** argc){
   glu = new GLUtil();
   gLog = new GameLogic();
   glu->initialize(&argv, argc, idle, draw);
   glu->reshapeWindow(def_width, def_height);
   glu->setResolution(def_width, def_height);
   glu->renameWindow(dos_title);
   glu->start();
   return 0;
}
