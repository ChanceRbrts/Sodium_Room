
#include "instance.h"

Instance::Instance(double X, double Y, double W, double H){
   x = X*32;
   y = Y*32;
   w = W*32;
   h = H*32;
   dX = 0;
   dY = 0;
   r = 1;
   g = 1;
   b = 1;
   termY = 1024;
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
   name = "Instance";
}

void Instance::doGravity(double deltaTime){
   dY += 1024*deltaTime;
   if (dY > termY) dY = termY;
}

void Instance::upd(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
   if (gravity) doGravity(deltaTime);
   update(deltaTime, keyPressed, keyHeld, player);
   onGround = false;
}

void Instance::finishUpdate(double deltaTime){
   x += dX*deltaTime;
   y += dY*deltaTime;
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

void Instance::draw(GLUtil* glu){
   if (!hidden && !needExtra){
      draw(glu->draw, glu->shade);
   } else if (!hidden){
      drawEX(glu);
   }
}

void Instance::drawEX(GLUtil* glu){
   draw(glu->draw, glu->shade);
}

void Instance::draw(GLDraw* gld, GLShaders* gls){
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
      // If it's not solid, we just need to check the bounds of the object.
      if (y+dY*deltaTime < o->y+o->h+o->dY*deltaTime && y+h+dY*deltaTime > o->y+o->dY*deltaTime
            && x+dX*deltaTime < o->x+o->w+o->dX*deltaTime && x+w+dX*deltaTime > o->x+o->dX*deltaTime){
         collided(o, deltaTime);
         o->collided(this, deltaTime);
      }
   }
}

void Instance::arcCollision(Arc* o, double deltaTime){
   double oX = o->getX();
   double oY = o->getY();
   double r = o->getR();
   double fX = x-oX+dX*deltaTime;
   double fY = y-oY+dY*deltaTime;
   // If the instance is just out of reach of the circle of the arc, don't do anything.
   if (fX > r || fX+w < -r || fY > r || fY+h < -r) return;
   // Get arc degrees
   double d1 = o->getD1();
   double d2 = o->getD2();
   // Convert corners into polar coordinates.
   double rO = sqrt(fX*fX+fY*fY);
   double dO = atan2(fY, fX);
   // See if those coordinates go into the rectangle created by the arc.

}
