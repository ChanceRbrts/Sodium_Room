/**
 * Deals with SDL and OpenGL 2
 * If we need OpenGL 3 or 4, this shouldn't be too hard of a translation.
 */
#ifndef dos_sdl2
#define dos_sdl2
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
// This is how SDL installed on my Mac when I installed it.
// If it turns out that this is not where SDL is actually installed, then I'll add compiler flags.
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// SDL_Info is a wrapper to get SDL specific information into our GLUtil class.
struct SDL_Info{
   SDL_Window* window;
   void (*idle)();
   void (*display)();
};

#endif