#include "../glUtil.h"
#include "glut.h"

GLUtil::GLUtil(){
   glVersion = 2.1;
   control = new GLControls(nullptr);
   shade = new GLShaders(nullptr);
   draw = new GLDraw(1, 1, nullptr);
}

void GLUtil::initialize(int* argc, char** argv, void (*idle)(), void (*display)()){
   glutInit(argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutCreateWindow("");
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutKeyboardFunc(control->keyDown);
   glutKeyboardUpFunc(control->keyUp);
   glutSpecialFunc(control->specialKey);
   glutSpecialUpFunc(control->specialKeyUp);
   glutMouseFunc(control->mouseFunc);
   glutMotionFunc(control->mouseMotion);
   glutPassiveMotionFunc(control->mousePassMotion);
   glutReshapeFunc(reshape);
}

void GLUtil::reshape(int width, int height){
}

void GLUtil::reshapeWindow(int width, int height){
   glutReshapeWindow(width, height);
}

void GLUtil::renameWindow(std::string newName){
   glutSetWindowTitle(newName.c_str());
}

void GLUtil::start(){
   glutMainLoop();
}

double GLUtil::getTime(){
   return glutGet(GLUT_ELAPSED_TIME);
}

void GLUtil::redisplay(){
   glutPostRedisplay();
}

void GLUtil::setResolution(int width, int height){
   delete draw;
   draw = new GLDraw(width, height, nullptr);
}