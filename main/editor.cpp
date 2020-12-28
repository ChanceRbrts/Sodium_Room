/*
#include "../glutils/glUtil.h"
#include "../editorFiles/editorLogic.h"

GLUtil* glu;
EditorLogic* ed;
double curTime = 0;
bool displ = true;

void idle(){
   double newTime = glu->getTime()/1000.0;
   if (curTime != 0){
      float deltaTime = newTime-curTime;
      ed->update(deltaTime, glu);
      glu->redisplay();
      displ = true;
   }
   curTime = newTime;
}

void draw(){
   if (displ){
      glu->draw->start();
      ed->draw(glu);
      glu->draw->finish();
      displ = false;
   }
}

int main(int argv, char** argc){
   glu = new GLUtil();
   ed = new EditorLogic();
   glu->initialize(&argv, argc, idle, draw);
   glu->reshapeWindow(640, 480+48);
   glu->setResolution(640, 480+48);
   glu->renameWindow("Dream of Shading Editor");
   glu->start();
   return 0;
}
*/