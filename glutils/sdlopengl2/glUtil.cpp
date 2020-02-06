#include "../glUtil.h"
#include "sdl.h"

GLUtil::GLUtil(){
   glVersion = 2.1;
   SDL_Info* i = new SDL_Info();
   extraInfo = i;
   control = new GLControls(extraInfo);
   shade = new GLShaders(extraInfo);
   draw = new GLDraw(1, 1, extraInfo);
}

void GLUtil::initialize(int* argc, char** argv, void (*idle)(), void (*display)()){
   SDL_Info* info = (SDL_Info*)extraInfo;
   info->idle = idle;
   info->display = display;
   // Initialize SDL
   if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
      fprintf(stderr, "Error: No input value detected.");
      SDL_Quit();
      exit(1);
   }
   // Thanks https://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php for helping a little bit with the setup code.
   // Initialize OpenGL Parameters.
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   // Initialize our extensions.
   if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
      fprintf(stderr, "Error: Pngs can't be loaded!");
      SDL_Quit();
      IMG_Quit();
      exit(1);
   }
   if (TTF_Init() == -1){
      fprintf(stderr, "Error: Fonts can't be loaded!");
      TTF_Quit();
      SDL_Quit();
      IMG_Quit();
      exit(1);
   }
   // Create OpenGL Windows
   info->window = SDL_CreateWindow("", 0, 0, 640, 480, SDL_WINDOW_OPENGL);
   SDL_GL_CreateContext(info->window);
}

void GLUtil::reshape(int width, int height){}

void GLUtil::reshapeWindow(int width, int height){
   SDL_Info* info = (SDL_Info*)extraInfo;
   SDL_SetWindowSize(info->window, width, height);
}

void GLUtil::renameWindow(std::string newName){
   SDL_Info* info = (SDL_Info*)extraInfo;
   SDL_SetWindowTitle(info->window, newName.c_str());
}

void GLUtil::start(){
   // Create the main loop here.
   SDL_Info* info = (SDL_Info*)extraInfo;
   while (1){
      // Control
      control->controlLoop();
      // Update
      info->idle();
      // Draw
      info->display();
   }
}

double GLUtil::getTime(){
   return SDL_GetTicks();
}

void GLUtil::redisplay(){}

void GLUtil::setResolution(int width, int height){
   delete draw;
   draw = new GLDraw(width, height, extraInfo);
}
