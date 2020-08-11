#include "../glUtil.h"
#include "glut.h"

GLDraw::GLDraw(double wid, double hei, void* eInfo){
   mode = 0;
   normalCalc = false;
   maxVerts = 0;
   vert = 0;
   width = wid;
   height = hei;
   texGen = new GLTextureGen(eInfo);
}

GLDraw::~GLDraw(){
   vertices.clear();
   colors.clear();
   texts.clear();
   tempVert.clear();
   tempCol.clear();
   tempTex.clear();
   while (headCam != nullptr){
      cameraMem* delCam = headCam;
      headCam = headCam->prev;
      delete delCam;
   }
}

int GLDraw::toMode(std::string type){
   if (type.compare("GL_QUADS") == 0 || type.compare("QUADS") == 0) return GL_QUADS;
   if (type.compare("GL_TRIANGLES") == 0 || type.compare("TRIANGLES") == 0) return GL_TRIANGLES;
   if (type.compare("GL_LINES") == 0 || type.compare("LINES") == 0) return GL_LINES;
   if (type.compare("GL_POINTS") == 0 || type.compare("POINTS") == 0) return GL_POINTS;
   return -1;
}

void GLDraw::begin(std::string type){
   begin(toMode(type));
}

void GLDraw::begin(int type){
   glBegin(type);
   mode = type;
   if (mode == GL_TRIANGLES || mode == GL_TRIANGLE_FAN || mode == GL_TRIANGLE_STRIP){
      maxVerts = 3;
   }
   if (mode == GL_QUADS || mode == GL_QUAD_STRIP){
      maxVerts = 4;
   }
}

void GLDraw::bindTexture(int tex, int texLayer, bool backToNormal){
   if (texLayer > 31) return;
   glActiveTexture(GL_TEXTURE0+texLayer);
   glBindTexture(GL_TEXTURE_2D, tex);
   // Let's not mess up any actual drawing.
   if (backToNormal) glActiveTexture(GL_TEXTURE0);
}

void GLDraw::enableTextures(){
   glEnable(GL_TEXTURE_2D);
}

void GLDraw::disableTextures(){
   glDisable(GL_TEXTURE_2D);
}

void GLDraw::normal(double n1, double n2, double n3){
   glNormal3d(n1, n2, n3);
   normalCalc = false;
}

void GLDraw::calculateNormals(){
   normalCalc = true;
}

void GLDraw::color(double r, double g, double b){
   glDisable(GL_BLEND);
   glColor3d(r, g, b);
}

void GLDraw::color(double r, double g, double b, double a){
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glColor4d(r, g, b, a);
}

void GLDraw::color(double r, double g, double b, double a, bool blend){
   blend ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
   if (blend) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glColor4d(r, g, b, a);
}

void GLDraw::texCoords(double s, double t){
   glTexCoord2d(s, t);
}

void GLDraw::drawArray(float* verts, float* cols, float* texs, int size, int vertGap, int colGap, int type){
   /*if (type != GL_POINTS || type != GL_LINES || type != GL_TRIANGLE_FAN || type != GL_TRIANGLES){   
      fprintf(stderr, "Type not applicable with drawArray");
   }*/
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GLDraw::vertex(double v1, double v2, double v3){
   // printf("%d, %d\n", GL_QUADS, mode);
   if (!(mode == GL_TRIANGLES || mode == GL_QUADS) || !normalCalc){
      glVertex3d(v1, v2, v3);
      return;
   }
   // TODO: Calculate lighting for triangles, quads, triangle fans, quad strips, and polygons automatically.
   
}

void GLDraw::pushMatrix(){
   glPushMatrix();
}

void GLDraw::popMatrix(){
   glPopMatrix();
}

void GLDraw::translate(double x, double y, double z){
   glTranslated(x, y, z);
}

void GLDraw::scale(double w, double h, double l){
   glScaled(w, h, l);
}

void GLDraw::rotate(double angle, double x, double y, double z){
   glRotated(angle, x, y, z);
}

void GLDraw::end(){
   glEnd();
}

void GLDraw::start(){
   glClearColor(0.5, 0.5, 0.5, 1.0);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
}

void GLDraw::finish(){
   glPopAttrib();
   glFlush();
   glutSwapBuffers();
}

void GLDraw::finishNoDraw(){
   glPopAttrib();
   glFlush();
}
