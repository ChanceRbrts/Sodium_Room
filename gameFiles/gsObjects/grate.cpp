#include "grate.h"

Grate::Grate(double X, double Y, double W) : Instance(X, Y, W, 1){
   immovable = true;
   r = 0.7;
   g = 0.7;
   b = 0.7;
   name = "Grate";
   loadedTexture = false;
}

void Grate::loadTexture(){
   if (TexBook::hasTexture("resources/misc/grate.png")){
      changeTexture(TexBook::getTexture("resources/misc/grate.png"), true);
   } else{
      int tex = TexBook::loadTexture("resources/misc/grate.png");
      if (tex != -1) changeTexture(tex, true);
   }
}

void Grate::draw(GLDraw* gld, GLShaders* gls, int layer){
   if (!loadedTexture){
      loadTexture();
      loadedTexture = true;
   } 
   if (hasTexture){
      gld->enableTextures();
      gld->bindTexture(textureID);
      gld->color(r,g,b,1);
   }
   else gld->color(r,g,b);
   gld->begin("QUADS");
   // Now, we have to divide this up into squares to draw based off of texIDs.
   int s = w/32;
   for (int i = 0; i < s; i++){
      double texOffset = 0;
      if (s == 1) texOffset = 0.75;
      else if (i == s-1) texOffset = 0.5;
      else if (i > 0) texOffset = 0.25;
      gld->texCoords(texOffset, 0);
      gld->vertW(x+i*32,y);
      gld->texCoords(texOffset, 1);
      gld->vertW(x+i*32,y+h);
      gld->texCoords(texOffset+0.25, 1);
      gld->vertW(x+(i+1)*32,y+h);
      gld->texCoords(texOffset+0.25, 0);
      gld->vertW(x+(i+1)*32,y);
   }
   gld->end();
   if (hasTexture){
      gld->bindTexture(0);
      gld->disableTextures();
   }
}
