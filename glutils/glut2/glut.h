/** 
 * Deals with GLUT and OpenGL 2.
 * If we need OpenGL 3 or 4, that shouldn't be too hard of a translation.
 */

#ifndef dos_glut2
#define dos_glut2
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GLUT/glut.h"
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#endif
#endif