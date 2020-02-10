#include "level.h"

Level::Level(){
   filePath = "";
   createdShaderboxes = false;
   insts = nullptr;
   hasBackground = false;
   r = 0.5;
   g = 0.5;
   b = 0.5;
}

Level::~Level(){
   destroyLevel();
}

pointDouble Level::createLevel(){
   pointDouble defaultPoint = (pointDouble){-1, -1, -1};
   std::vector<Instance*> instances;
   // First, load any solid map associated with the level.
   if (filePath.length() > 0){
      // Looks for the solid map here.
      FILE* f = fopen((std::string("gameFiles/levels/levelData/")+filePath+".txt").c_str(), "r");
      if (f == nullptr){
         fprintf(stderr, "ERROR: %s doesn't exist.\n", (filePath+".txt").c_str());
         return defaultPoint;
      } 
      std::string line = "";
      int mode = DEFAULT;
      int yVal = 0;
      int wid = 0;
      // Parse through our solid map.
      while (!feof(f)){
         char c = fgetc(f);
         if (c == '\n' || feof(f)){
            if (mode == TEXTURES){
               // Look for textures layout. (TODO)
            } else if (mode == LAYOUT){
               // Look for the layout of the build.
               for (int i = 0; i < line.length(); i++){
                  if (line[i] != ' '){
                     // TODO: Add textures to this solid object?
                     instances.push_back(new Solid(i,yVal));
                  }
               }
               if (line.length() > wid) wid = line.length();
               yVal += 1;
            }
            if (line.find("Textures") != std::string::npos){
               mode = TEXTURES;
            } else if (line.find("Layout") != std::string::npos){
               mode = LAYOUT;
            }
            line = "";
         } else {
            line += c;
         }
      }
      w = wid*32;
      h = yVal*32;
   }
   instances = makeLevel(instances);
   while (insts != nullptr){
      Instances* del = insts;
      insts = insts->next;
      delete del;
   }
   Instances* is = nullptr;
   // Let's make sure really quickly that we didn't add a memory leak in inst
   for (int i = 0; i < instances.size(); i++){
      if (instances[i]->isPlayer()){
         // If it's a player, return their coordinates.
         defaultPoint.x = instances[i]->x;
         defaultPoint.y = instances[i]->y;
      } else {
         // Otherwise, put it in the doubly linked list.
         Instances* inst = new Instances();
         inst->i = instances[i];
         if (is == nullptr){
            is = inst;
            // We are at the start of the linked list.
            insts = inst;
         } else {
            // Add stuff to the next part of the linked list.
            is->next = inst;
            inst->prev = is;
            is = inst;
         }
      }
   }
   instances.clear();
   return defaultPoint;
}

void Level::destroyLevel(){
   // Deallocate out shader boxes here.
   for (int i = 0; i < shades.size(); i++){
      delete shades[i];
   }
   shades.clear();
   // Deallocate our level here.
   while (insts != nullptr){
      Instances* del = insts;
      insts = insts->next;
      delete del;
   }
   // In case we remake this level, we should have it remake our shaderboxes.
   createdShaderboxes = false;
}

std::vector<Instance*> Level::makeLevel(std::vector<Instance*> previous){
   return previous;
}

std::vector<ShaderBox*> Level::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox*> empty;
   return empty;
}

void Level::draw(GLUtil* glu, Instance* player){
   if (hasBackground){
      // TODO: Draw the background.
   }
   // Make sure we're drawing our shaderboxes first.
   if (!createdShaderboxes){
      shades = createShaderBoxes(glu);
      createdShaderboxes = true;
   }
   // Draw our objects once.
   drawObjects(glu, player, 0);
   // Draw everything to each of the shader boxes, then draw that shaderbox.
   for (int i = 0; i < shades.size(); i++){
      ShaderBox* shade = shades[i];
      shade->drawOnBox();
      drawObjects(glu, player, 0);
      shade->drawOutBox();
      shade->draw();
   }
}

void Level::drawObjects(GLUtil* glu, Instance* player, int mode){
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   double cX = glu->draw->camX;
   double cY = glu->draw->camY;
   if (player != nullptr){
      if (player->x < cX+wid && player->x+player->w > cX && player->y < cY+hei && player->y+player->h > cY){
            player->draw(glu);
         }
   }
   if (insts != nullptr){
      for (Instances* i = insts; i != nullptr; i = i->next){
         Instance* in = i->i;
         /*if (in->getName().compare("Enclosed Level") == 0){
            printf("%f, %f, %f, %f\n", in->x, in->y, in->w, in->h);
         }*/
         // Check if the instance is in the bounds of the screen.
         if (in->x < cX+wid && in->x+in->w > cX && in->y < cY+hei && in->y+in->h > cY){
            in->draw(glu);
         } 
      }
   }
}

void Level::moveInstance(Instances* move, Level* otherLev){
   if (move->prev == nullptr){
      // We got the head of our linked list
      insts = move->next;
   } else {
      move->prev->next = move->next;
   }
   // Move this to the beginning of the other linked list.
   move->prev = nullptr;
   move->next = otherLev->insts;
   Instance* i = move->i;
   i->x += otherLev->xOff-xOff;
   i->y += otherLev->yOff-yOff;
   otherLev->insts = move->next;
}

void Level::moveOutOfBounds(void* lv){
   LevelList* lev = (LevelList *)lv;
   if (lev == nullptr) return;
   // For now, this is a simple out of bounds checker.
   Instances* i = insts;
   while (i != nullptr){
      // Consider the midpoint of an instance.
      double pointX = i->i->x+i->i->w/2;
      double pointY = i->i->y+i->i->h/2;
      Instances* next = i->next;
      // If that midpoint is outside of the current level, we need to move it to another level.
      if (pointX < xOff || pointX > xOff+w*32 || pointY < yOff || pointY > yOff+h*32){
         for (LevelList* l = lev; l != nullptr; l = l->next){
            if (l->lev != this){
               Level* level = l->lev;
               if (pointX >= level->xOff && pointX <= level->xOff+level->w &&
                     pointY >= level->yOff && pointY <= level->yOff+level->h){
                  // Move the instance to this level.
                  moveInstance(i, level);
                  break;
               }
            }
         }
      }
      i = next;
   }
   // TODO(?): Greedy checker to see if an object from an enclosing room has fallen into bounds.
   return;
}

float Level::getXOff(){ return xOff; }

float Level::getYOff(){ return yOff; }

void Level::moveRoom(float newXOff, float newYOff, bool relative){
   float oldXOff = xOff;
   float oldYOff = yOff;
   xOff = relative ? xOff+newXOff : newXOff;
   yOff = relative ? yOff+newYOff : newYOff;
   // Move all of the instances to the level's new offsets.
   if (insts == nullptr) return;
   for (Instances* i = insts; i != nullptr; i = i->next){
      insts->i->x += xOff-oldXOff;
      insts->i->y += yOff-oldYOff;
   }
}

void Level::bisectLevel(bool horizontal, float splitLocation, float offset, Instance* cause){
   if (horizontal){ 
      w += offset;
   } else{
      h += offset;
   } 
   if (insts == nullptr) return;
   for (Instances* i = insts; i != nullptr; i = i->next){
      if (i->i != cause && horizontal && i->i->x-xOff >= splitLocation){
         i->i->x += offset;
      } else if (i->i != cause && !horizontal && i->i->y-yOff >= splitLocation) {
         i->i->y += offset;
      }
   }
}
