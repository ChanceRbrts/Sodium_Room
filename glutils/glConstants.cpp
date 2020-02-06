// This class is for functions that should remain constant regardless of which Graphics Library is being used.
#include "glUtil.h"

bool GLDraw::popCameraMem(){
   if (headCam == nullptr) return false;
   cameraMem* realCam = headCam;
   headCam = headCam->prev;
   camX = realCam->x;
   camY = realCam->y;
   width = realCam->w;
   height = realCam->h;
   delete realCam;
   return true;
}

void GLDraw::pushCameraMem(double x, double y, double w, double h){
   cameraMem* prevCam = new cameraMem((cameraMem){camX, camY, width, height, headCam});
   headCam = prevCam;
   camX = x;
   camY = y;
   width = w;
   height = h;
}

pointDouble GLDraw::vPoint(double v1, double v2){
   return (pointDouble){(v1-camX)*2/width-1, 1-(v2-camY)*2/height, 0};
}

intStack* GLShaders::popIntStack(intStack* is){
   if (is == nullptr) return nullptr;
   is = is->prev;
   return is;
}

intStack* GLShaders::pushIntStack(intStack* is, int i){
   intStack* newIS = new intStack((intStack){i, is});
   is = newIS;
   return is;
}

pointInt GLControls::getMouseInfo(){
   return (pointInt){mouseX, mouseY, mousePressed};
}
