
#include "instance.h"

Instance::Instance(double X, double Y, double W, double H){
   x = X*32;
   y = Y*32;
   w = W*32;
   h = H*32;
   dX = 0;
   prevDX = dX;
   dY = 0;
   prevDY = dY;
   r = 1;
   g = 1;
   b = 1;
   termY = 1024;
   dXModifier = 1;
   dYModifier = 1;
   startDXM = 0;
   startDYM = 0;
   targetDXM = 0;
   targetDYM = 0;
   dXChangeTime = 0;
   dYChangeTime = 0;
   collDX = 0;
   collDY = 0;
   textureID = -1;
   hasTexture = false;
   gravity = false;
   onGround = false;
   immovable = false;
   remove = false;
   playerRef = false;
   solid = true;
   hidden = false;
   needExtra = false;
   stuckToWall = false;
   name = "Instance";
   initLayers();
}

std::vector<int> Instance::initLayers(){
   layers.push_back(LAYER_NORMAL);
   return layers;
}

void Instance::doGravity(double deltaTime){
   if (termY > 0){
      dY += 1024*deltaTime;
      if (dY > termY) dY = termY;
   } else {
      dY -= 1024*deltaTime;
      if (dY < termY) dY = termY;
   }
}

void Instance::upd(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
   if (gravity) doGravity(deltaTime);
   update(deltaTime, keyPressed, keyHeld, player);
   onGround = false;
   // Arc collision happens directly after the update frame.
   // Due to when the arc collision happens, this makes sure the arc still has an effect for one frame.
   arcList.clear();
   for (int i = 0; i < 2; i++){
      double* dStart = (i == 0)? &startDXM : &startDYM;
      double* dEnd = (i == 0)? &targetDXM : &targetDYM;
      double* dTime = (i == 0)? &dXChangeTime : &dYChangeTime;
      double* dVModifier = (i == 0)? &dXModifier : &dYModifier;
      // If no speed change is in effect, don't try to change the speed!
      if (*dTime <= 0 || abs(*dVModifier-*dEnd) < 0.01) continue;
      double dDV = deltaTime*(*dEnd-*dStart)/(*dTime);
      *dVModifier += dDV;
      // Note when we end the linear interpolation
      int modifier = (dDV > 0) ? 1 : -1;
      if ((*dVModifier-*dEnd)*modifier > 0){
         *dTime = 0;
         *dVModifier = *dEnd;
      } 
   }
   // Apply the multiplier.
   dX *= dXModifier == 0 ? 0.001 : dXModifier;
   dY *= dYModifier == 0 ? 0.001 : dYModifier;
   collDX = dX;
   collDY = dY;
}

void Instance::finishUpdate(double deltaTime){
   x += dX*deltaTime;
   y += dY*deltaTime;
   dX /= dXModifier == 0 ? 0.001 : dXModifier;
   dY /= dYModifier == 0 ? 0.001 : dYModifier;
   prevDX = dX;
   prevDY = dY;
   fUpdate(deltaTime);
}

void Instance::changeTexture(int tex, bool untint){
   textureID = tex;
   hasTexture = true;
   if (untint){
      r = 1;
      g = 1;
      b = 1;
   }
}

void Instance::hide(bool h){
   hidden = h;
}

void Instance::changeDVModifier(bool horizontal, double to, double timeMod, bool changeSpeed){
   double* startDVM = horizontal? &startDXM : &startDYM;
   double* targetDVM = horizontal? &targetDXM : &targetDYM;
   double* dVChangeTime = horizontal? &dXChangeTime : &dYChangeTime;
   double* dVModifier = horizontal? &dXModifier : &dYModifier;
   double* dV = horizontal? &dX : &dY;
   *startDVM = *dVModifier;
   *targetDVM = to;
   if (changeSpeed){
      *dVChangeTime = 0;
      *dVModifier = to;
      *dV = (*dV)*(*startDVM)/to;
      return;
   }
   *dVChangeTime = timeMod;
}

void Instance::draw(GLUtil* glu, int layer){
   if (!hidden && !needExtra){
      draw(glu->draw, glu->shade, layer);
   } else if (!hidden){
      drawEX(glu, layer);
   }
}

void Instance::drawEX(GLUtil* glu, int layer){
   draw(glu->draw, glu->shade, layer);
}

void Instance::draw(GLDraw* gld, GLShaders* gls, int layer){
   if (hasTexture){
      gld->enableTextures();
      gld->bindTexture(textureID);
      gld->color(r,g,b,1);
   }
   else gld->color(r,g,b);
   // Draws a rectangle with colors r, g, and b.
   gld->begin("QUADS");
   gld->texCoords(0, 0);
   gld->vertW(x,y);
   gld->texCoords(0, 1);
   gld->vertW(x,y+h);
   gld->texCoords(1, 1);
   gld->vertW(x+w,y+h);
   gld->texCoords(1, 0);
   gld->vertW(x+w,y);
   gld->end();
   if (hasTexture){
      gld->bindTexture(0);
      gld->disableTextures();
   }
}

bool Instance::isSolid(std::string other){
   for (int i = 0; i < colList.size(); i++){
      if (colList[i].compare(other) == 0) return !solid;
   }
   return solid;
}

void Instance::collision(Instance* o, double deltaTime, bool cornerCheck){
   // Make sure everything's solid before continuing.
   if (o->isSolid(name) && isSolid(o->name)){
      // Check If Colliding with Bottom of Other Instance
      if (y+dY*deltaTime < o->y+o->dY*deltaTime+o->h && y >= o->y+o->h 
            && x+w+dX*deltaTime*cornerCheck > o->x+o->dX*deltaTime*cornerCheck 
            && x+dX*deltaTime*cornerCheck < o->x+o->w+o->dX*deltaTime*cornerCheck){
         dY = o->immovable?o->dY:0;
         o->dY = immovable?dY:0;
         y = immovable?y:o->y+o->h;
         o->y = o->immovable?o->y:y-o->h;
         collided(o, deltaTime);
         o->collided(this, deltaTime);
         o->onGround = true;
      } // Check If Colliding with Top of Other Instance
      else if (y+h+dY*deltaTime > o->y+o->dY*deltaTime && y+h <= o->y 
            && x+w+dX*deltaTime*cornerCheck > o->x+o->dX*deltaTime*cornerCheck 
            && x+dX*deltaTime*cornerCheck < o->x+o->w+o->dX*deltaTime*cornerCheck){
         dY = o->immovable?o->dY:0;
         o->dY = immovable?dY:0;
         y = immovable?y:o->y-h;
         o->y = immovable?o->y:y+h;
         collided(o, deltaTime);
         o->collided(this, deltaTime);
         onGround = true;
      } 
      // Check If Colliding with Left of Other Instance
      if (x+dX*deltaTime < o->x+o->dX*deltaTime+o->w && x >= o->x+o->w 
            && y+h+dY*deltaTime*cornerCheck > o->y+o->dY*deltaTime*cornerCheck 
            && y+dY*deltaTime*cornerCheck < o->y+o->h+o->dY*deltaTime*cornerCheck){
         dX = o->immovable?o->dX:0;
         o->dX = immovable?dX:0;
         x = immovable?x:o->x+o->w;
         o->x = o->immovable?o->x:x-o->w;
         collided(o, deltaTime);
         o->collided(this, deltaTime);
      } // Check If Colliding with Right of Other Instance
      else if (x+w+dX*deltaTime > o->x+o->dX*deltaTime && x+w <= o->x 
            && y+h+dY*deltaTime*cornerCheck > o->y+o->dY*deltaTime*cornerCheck 
            && y+dY*deltaTime*cornerCheck < o->y+o->h+o->dY*deltaTime*cornerCheck){
         dX = o->immovable?o->dX:0;
         o->dX = immovable?dX:0;
         x = immovable?x:o->x-w;
         o->x = immovable?o->x:x+w;
         collided(o, deltaTime);
         o->collided(this, deltaTime);
      }
   } else{
      float rDX = o->stuckToWall ? collDX : dX;
      float rDY = o->stuckToWall ? collDY : dY;
      float oRDX = stuckToWall ? o->collDX : o->dX;
      float oRDY = stuckToWall ? o->collDY : o->dY;
      // If it's not solid, we just need to check the bounds of the object.
      if (y+rDY*deltaTime < o->y+o->h+oRDY*deltaTime && y+h+rDY*deltaTime > o->y+oRDY*deltaTime
            && x+rDX*deltaTime < o->x+o->w+oRDX*deltaTime && x+w+rDX*deltaTime > o->x+oRDX*deltaTime){
         collided(o, deltaTime);
         o->collided(this, deltaTime);
      }
   }
}

bool Instance::arcCollision(Arc* o, double deltaTime){
   double oX = o->getX();
   double oY = o->getY();
   double r = o->getR();
   double fX = x-oX+dX*deltaTime;
   double fY = y-oY+dY*deltaTime;
   // If the instance is just out of reach of the circle of the arc, don't do anything.
   if (fX > r || fX+w < -r || fY > r || fY+h < -r) return false;
   // What makes this easier is the fact that the instance is grid aligned.
   // As such, if the center is in that area, then we have a collision
   if (fX <= 0 && fY <= 0 && fX+w >= 0 && fY+h >= 0) return true;
   // Of course, if it's not any of these cases, we have to be more creative...
   // First, we need to check the radian ranges of the instance compared to the arc.
   // Get arc degrees
   double d1 = fmod(o->getD1()+M_PI, 2*M_PI)-M_PI;
   double d2 = fmod(o->getD2()+M_PI, 2*M_PI)-M_PI;
   double d2A = d1 > d2 ? d2 + 2*M_PI : d2;
   // If d1 > d2, then there's wrap around that we have to deal with.
   // Compare the four corners of the hitbox to the arc in polar coordinates.
   bool q1 = false;
   bool q2 = false;
   bool q3 = false;
   bool q4 = false;
   for (int i = 0; i < 4; i++){
      // Go through each corner in connecting location.
      double xi = fX+w*int(i/2);
      double yi = fY+h*int((i-1)/2);
      // We don't need to worry about this being 0.
      double ri = sqrt(xi*xi+yi*yi);
      double di = atan2(yi, xi);
      double dj = di;
      dj += (di < d1 && d1 > d2) ? 2*M_PI : 0;
      if (dj >= d1 && dj <= d2A && ri <= r) return true;
      // Find the quadrant this is in and make a note to check that quadrant.
      if (di <= -M_PI_2) q3 = true;
      else if (di <= 0) q4 = true;
      else if (di <= M_PI_2) q1 = true;
      else q2 = true;
   }
   // Check in 2 degree rays past the arc.
   // (4 degrees at a 320 px radius takes about 32 px. (2*pi*320/(360/4)))
   d2 += (d1 >= d2) ? 2*M_PI : 0;
   for (double di = d1; di <= d2; di += M_PI/45){
      double fXN = fX;
      double fXF = fX+w;
      double fYN = fY;
      double fYF = fY+h;
      // Move stuff to -PI to PI (3*PI is added to avoid negative numbers)
      double dj = fmod(di+3*M_PI, M_PI*2)-M_PI;
      // If the ray is in the wrong quadrant, move on to the next ray.
      // TODO: The actual line/rectangle collision stuff.
      if (dj <= -M_PI_2){
         // Check Bottom and Right.
         if (!q3) continue;
         fXN = -(fX+w);
         fXF = -fX;
         fYN = -(fY+h);
         fYF = -fY;
      }
      else if (dj > -M_PI_2 && dj <= 0){
         if (!q4) continue;
         // Check Bottom and Left
         fYN = -(fY+h);
         fYF = -fY;
      }
      else if (dj > 0 && dj <= M_PI_2){
         if (!q1) continue;
         // Check Top and Left (No Change)
      }
      else { // if (dj > M_PI_2)
         if (!q2) continue;
         // Check Top and Right
         fXN = -(fX+w);
         fXF = -fX;
      }
      double cDI = cos(di);
      double sDI = sin(di);
      if (cDI != 0){
         double slope = abs(sDI/cDI);
         if (slope == 0){
            // Either continues or returns true.
            // We only need to check the x-axis in this case.
            if (fY > 0 || fY+h < 0) continue;
            if (cDI > 0 && fX > 0 && fX < r) return true;
            if (cDI < 0 && fX+w < 0 && fX+w > -r) return true;
         }
         // Check if there's an intersection horizontally. (Only need to check closest wall.)
         float testY = slope*fXN;
         if (testY >= fYN && testY <= fYF) return true;
         // Check if there's an intersection vertically. (Only need to check closest wall.)
         float testX = fYN/slope;
         if (testX >= fXN && testX <= fXF) return true;
      } else {
         // We only need to check the y-axis in this case.
         if (fX > 0 || fX+w < 0 ) continue;
         if (sDI > 0 && fY > 0 && fY < r) return true;
         if (sDI < 0 && fY+h < 0 && fY+h > -r) return true;
      }
   }
   // If there is no intersection, then we have not found anything.
   return false;
}

void Instance::arcCol(Arc* o, double deltaTime, int id){
   if (!arcCollision(o, deltaTime)) return;
   arcList.push_back(o->getInfo(id));
}
