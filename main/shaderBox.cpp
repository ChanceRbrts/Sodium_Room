#include "shaderBox.h"

ShaderBox::ShaderBox(double X, double Y, double W, double H, std::string vertShader, std::string fragShader, GLUtil* GLU){
   x = X*32;
   y = Y*32;
   w = W*32;
   h = H*32;
   xOffset = 0;
   yOffset = 0;
   follow = false;
   glu = GLU;
   // Sets up the framebuffer.
   struct upointInt frameBufferParts = glu->shade->createFrameBuffer();
   frameID = frameBufferParts.x;
   texID = frameBufferParts.y;
   renID = frameBufferParts.z;
   glu->shade->resizeFrameBuffer(frameID, texID, renID, w, h);
   drawID = vertShader+fragShader;
   if (drawID.length() > 0 && !glu->shade->programExists(drawID)){
      glu->shade->createProgram("gameFiles/shaders/"+vertShader, "gameFiles/shaders/"+fragShader, drawID);
   }
   fullID = "";
   remove = false;
   blend = true;
   fastDraw = true;
   drawBeforeArc = false;
   replaceWithArc = false;
   arcOne = nullptr;
   arcOneAlpha = nullptr;
   arcTwo = nullptr;
   arcTwoAlpha = nullptr;
}

ShaderBox::~ShaderBox(){
   glu->shade->deleteFrameBuffer(frameID, texID, renID);
   uniforms.clear();
}

void ShaderBox::drawOnBox(){
   GLDraw* gld = glu->draw;
   // Pushes the framebuffer onto the stack of framebuffers to draw to.
   if (x+w >= gld->camX && y+h >= gld->camY && x <= gld->camX+gld->getWidth() && y <= gld->camY+gld->getHeight()){
      glu->draw->pushCameraMem(x, y, w, h);
      glu->shade->bindFrameBuffer(frameID);
      glu->draw->start();
      if (fullID.length() > 0) glu->shade->bindShader(fullID);
   }
}

void ShaderBox::drawOutBox(){
   GLDraw* gld = glu->draw;
   // Pops the framebuffer off of the stack of framebuffers to draw to.
   if (x+w >= gld->camX && y+h >= gld->camY && x <= gld->camX+gld->getWidth() && y <= gld->camY+gld->getHeight()){
      if (fullID.length() > 0) glu->shade->unbindShader();
      glu->draw->finish();
      glu->shade->unbindFrameBuffer();
      glu->draw->popCameraMem();
   }
}

bool ShaderBox::canDraw(){
   GLDraw* gld = glu->draw;
   return (x+w+xOffset >= gld->camX && y+h+yOffset >= gld->camY 
         && x+xOffset <= gld->camX+gld->getWidth() && y+yOffset <= gld->camY+gld->getHeight());
}

void ShaderBox::draw(){
   // Draw only if we're within the bounds of the screen.
   if (canDraw()){
      // Get Shaders ready if we need them.
      int program = 0;
      if (drawID.length() > 0) program = glu->shade->bindShader(drawID);
      if (program > 0){
         for (std::map<std::string, float>::iterator it = uniforms.begin(); it != uniforms.end(); it++){
            // printf("%s, %f\n", it->first.c_str(), it->second);
            glu->shade->addUniform(program, it->first, it->second);
         }
         for (std::map<std::string, int>::iterator it = uniformIs.begin(); it != uniformIs.end(); it++){
            glu->shade->addUniformI(program, it->first, it->second);
         }
      }
      // else glu->shade->bindShader(0);
      // Draw our frame buffer to the screen!
      glu->draw->enableTextures();
      glu->draw->bindTexture(texID);
      // Actually draw the textures.
      glu->draw->color(1, 1, 1, 1, blend);
      glu->draw->begin("QUADS");
      glu->draw->texCoords(0, 1);
      glu->draw->vertW(x+xOffset, y+yOffset);
      glu->draw->texCoords(0, 0);
      glu->draw->vertW(x+xOffset, y+h+yOffset);
      glu->draw->texCoords(1, 0);
      glu->draw->vertW(x+w+xOffset, y+h+yOffset);
      glu->draw->texCoords(1, 1);
      glu->draw->vertW(x+w+xOffset, y+yOffset);
      glu->draw->end();
      glu->draw->bindTexture(0);
      glu->draw->disableTextures();
      // Reset Shaders back to where they were.
      if (drawID.length() > 0) glu->shade->unbindShader();
   }
}

void ShaderBox::drawBoundary(){
   GLDraw* gld = glu->draw;
   // Draw only if we're within the bounds of the screen.
   if (x+w+xOffset >= gld->camX && y+h+yOffset >= gld->camY 
         && x+xOffset <= gld->camX+gld->getWidth() && y+yOffset <= gld->camY+gld->getHeight()){
      // Draw a red transparent rectangle where our bounds are supposed to be.
      gld->color(1, 0, 0, 0.25);
      gld->begin("QUADS");
      gld->vertW(x+xOffset, y+yOffset);
      gld->vertW(x+xOffset, y+h+yOffset);
      gld->vertW(x+w+xOffset, y+h+yOffset);
      gld->vertW(x+w+xOffset, y+yOffset);
      gld->end();
   }
}

void ShaderBox::moveShaderBox(double X, double Y, bool movingLevel){
   x = X;
   y = Y;
   if (arcOne == nullptr) return;
   arcOne->moveShaderBox(X, Y, movingLevel);
   arcOneAlpha->moveShaderBox(X, Y, movingLevel);
   arcTwo->moveShaderBox(X, Y, movingLevel);
   arcTwoAlpha->moveShaderBox(X, Y, movingLevel);
}

double ShaderBox::getX(){ return x; }

double ShaderBox::getY(){ return y; }

void ShaderBox::setXOffset(double xoffset){
   xOffset = xoffset;
}

void ShaderBox::setYOffset(double yoffset){
   yOffset = yoffset;
}

void ShaderBox::addUniform(std::string name, float value){
   uniforms[name] = value;
}

void ShaderBox::addUniformI(std::string name, int value){
   uniformIs[name] = value;
}

void ShaderBox::removeMe(){
   remove = true;
}

void ShaderBox::clearBox(){
   glu->draw->color(0, 0, 0, 1);
   glu->draw->begin("QUADS");
   glu->draw->texCoords(0, 1);
   glu->draw->vertW(x+xOffset, y+yOffset);
   glu->draw->texCoords(0, 0);
   glu->draw->vertW(x+xOffset, y+h+yOffset);
   glu->draw->texCoords(1, 0);
   glu->draw->vertW(x+w+xOffset, y+h+yOffset);
   glu->draw->texCoords(1, 1);
   glu->draw->vertW(x+w+xOffset, y+yOffset);
   glu->draw->end();
}

void ShaderBox::clearArcBoxes(){
   arcOneAlpha->drawOnBox();
   arcOneAlpha->clearBox();
   arcOneAlpha->drawOutBox();
   arcTwoAlpha->drawOnBox();
   arcTwoAlpha->clearBox();
   arcTwoAlpha->drawOutBox();
}

unsigned int ShaderBox::getTextureID(){
   return texID;
}

bool ShaderBox::changeShader(std::string dID){
   if (dID.length() > 0 && !glu->shade->programExists(dID)) return false;
   drawID = dID;
   return true;
}

bool ShaderBox::changeShader(std::string vert, std::string frag){
   std::string dID = vert+frag;
   if (dID.length() == 0 || glu->shade->programExists(dID)){
      drawID = dID;
      return true;
   }
   int val = glu->shade->createProgram("gameFiles/shaders/"+vert, "gameFiles/shaders/"+frag, dID);
   if (val == 0) return false;
   drawID = dID;
   return true;
}

void ShaderBox::setBlend(bool b){
   blend = b;
}

void ShaderBox::setDrawBeforeArc(bool b){
   drawBeforeArc = b;
   if (b) replaceWithArc = false;
   setFastDraw(fastDraw);
}

void ShaderBox::setReplaceWithArc(bool b){
   replaceWithArc = b;
   if (b) drawBeforeArc = false;
   setFastDraw(fastDraw);
}

void ShaderBox::setFastDraw(bool fD){
   fastDraw = fD;
   bool noShaderboxes = fastDraw || drawBeforeArc || replaceWithArc;
   if (noShaderboxes && arcOne != nullptr){
      delete arcOne;
      arcOne = nullptr;
      delete arcTwo;
      arcTwo = nullptr;
   } else if (!noShaderboxes) {
      arcOne = new ShaderBox(x/32, y/32, w/32, h/32, "", "drawArc", glu);
      arcOneAlpha = new ShaderBox(x/32, y/32, w/32, h/32, "", "", glu);
      arcTwo = new ShaderBox(x/32, y/32, w/32, h/32, "", "drawArc", glu);
      arcTwoAlpha = new ShaderBox(x/32, y/32, w/32, h/32, "", "", glu);
   }
}
