#include "level.h"

Level::Level(){
   filePath = "";
   createdShaderboxes = false;
   insts = nullptr;
   hasBackground = false;
   r = 0.5;
   g = 0.5;
   b = 0.5;
   w = 0;
   h = 0;
   xOff = 0;
   yOff = 0;
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
      std::map<char, int> textureMap;
      // Parse through our solid map.
      while (!feof(f)){
         char c = fgetc(f);
         if (c == '\n' || feof(f)){
            if (mode == TEXTURES){
               // Parsed as C Picture
               if (line.length() > 2 && line[1] == ' '){
                  char rep = line[0];
                  // Get the integer corresponding to the texture (Adding it in if necessary.)
                  std::string texPath = "resources/solids/"+line.substr(2)+".png";
                  int pTex = TexBook::loadTexture(texPath);
                  int tex = pTex > -1 ? pTex : TexBook::loadTexture(texPath);
                  if (tex > -1) textureMap.insert({rep, tex});
               }
            } else if (mode == LAYOUT){
               // Look for the layout of the build.
               for (int i = 0; i < line.length(); i++){
                  if (line[i] != ' '){
                     Solid* s = new Solid(i, yVal);
                     // Add textures to this solid object. (If they exist.)
                     if (textureMap.find(line[i]) != textureMap.end()){
                        s->changeTexture(textureMap.at(line[i]), true);
                     }
                     instances.push_back(s);
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
      textureMap.clear();
      w = wid*32;
      h = yVal*32;
   }
   instances = makeLevel(instances);
   arcs = createArcs();
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
   // Deallocate our arcs here.
   for (int i = 0; i < arcs.size(); i++){
      delete arcs[i];
   }
   arcs.clear();
   // Deallocate our shader boxes here.
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

std::vector<Arc*> Level::createArcs(){
   std::vector<Arc*> empty;
   return empty;
}

void Level::draw(GLUtil* glu, Instance* player){
   if (hasBackground){
      GLDraw* gld = glu->draw;
      // TODO: Draw the background.
      gld->color(r,g,b);
      // Draws a rectangle with colors r, g, and b.
      gld->begin("QUADS");
      gld->vertW(xOff,yOff);
      gld->vertW(xOff,yOff+h);
      gld->vertW(xOff+w,yOff+h);
      gld->vertW(xOff+w,yOff);
      gld->end();
   }
   // Update our arcs here. 
   // (Doing this before creating the shaderboxes so we don't have a ton of nullptrs.)
   for (int i = 0; i < arcs.size(); i++){
      arcs[i]->draw(glu);
   }
   // Make sure we're drawing our shaderboxes first.
   if (!createdShaderboxes){
      shades = createShaderBoxes(glu);
      for (int i = 0; i < arcs.size(); i++){
         shades.push_back(arcs[i]->getShaderBox());
      }
      createdShaderboxes = true;
   }
   // Draw our objects once.
   drawObjects(glu, player, 0);
   // Draw everything to each of the shader boxes, then draw that shaderbox.
   for (int i = 0; i < shades.size(); i++){
      ShaderBox* shade = shades[i];
      if (!(shade->canDraw())) continue;
      shade->drawOnBox();
      drawObjects(glu, player, 0);
      shade->drawOutBox();
      shade->draw();
   }
}

void Level::updateLevel(double deltaTime, Instance* player){
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
      i->i->x += xOff-oldXOff;
      i->i->y += yOff-oldYOff;
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
         // Probably a bad solution to this; could cause some unusual contracting.
         if (i->i->x-xOff < splitLocation) i->i->x = splitLocation+xOff;
      } else if (i->i != cause && !horizontal && i->i->y-yOff >= splitLocation) {
         i->i->y += offset;
         // Probably a bad solution to this; could cause some unusual contracting.
         if (i->i->y-yOff < splitLocation) i->i->y = splitLocation+yOff;
      }
   }
}
