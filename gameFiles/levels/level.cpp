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

void Level::setWidthHeight(){
   if (filePath.length() == 0) return;
   // Looks for the solid map here.
   FILE* f = fopen((std::string("gameFiles/levels/levelData/")+filePath+".txt").c_str(), "r");
   if (f == nullptr){
      fprintf(stderr, "ERROR: %s doesn't exist.\n", (filePath+".txt").c_str());
      return;
   } 
   std::string line = "";
   int mode = DEFAULT;
   int yVal = 0;
   int wid = 0;
   while (!feof(f)){
      char c = fgetc(f);
      if (c == '\n' || feof(f)){
         if (mode == LAYOUT){
            // Look for the layout of the build.
            // We just care about the line length and the number of lines.
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
   camObjs = createCameraObjects();
   while (insts != nullptr){
      Instances* del = insts;
      insts = insts->next;
      delete del;
   }
   Instances* is = nullptr;
   // Let's make sure really quickly that we didn't add a memory leak in inst
   for (int i = 0; i < instances.size(); i++){
      // Apply offsets here to translate objects directly to a level.
      instances[i]->x += xOff;
      instances[i]->y += yOff;
      if (instances[i]->isPlayer()){
         // If it's a player, return their coordinates.
         defaultPoint.x = instances[i]->x;
         defaultPoint.y = instances[i]->y;
         // Since we're not using the instance anymore, just remove it.
         delete instances[i];
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
         addToLayers(inst);
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
   // Deallocate our camera objects here.
   for (int i = 0; i < camObjs.size(); i++){
      delete camObjs[i];
   }
   camObjs.clear();
   // Deallocate our level here.
   while (insts != nullptr){
      Instances* del = insts;
      insts = insts->next;
      delete del;
   }
   // Deallocate our drawn layers here.
   std::map<int, Layer *>::iterator layerIt = layers.begin();
   while (layerIt != layers.end()){
      Layer* l = layerIt->second;
      DrawnInstance* dI = l->first;
      while (dI != nullptr){
         DrawnInstance* del = dI;
         dI = dI->next;
         delete del;
      }
      layerIt++;
   }
   layers.clear();
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

std::vector<CameraObject*> Level::createCameraObjects(){
   std::vector<CameraObject*> empty;
   return empty;
}

void Level::drawLayer(GLUtil* glu, int layer){
   if (layer == LAYER_BACK && hasBackground){
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
      return;
   }
   // Actually draw the objects in the current layer.
   drawObjects(glu, layer, 0);
}

bool Level::drawArcs(GLUtil* glu, ShaderBox* mainBox, DualSBox arcOne, DualSBox arcTwo, Instance* player){
   // Update arcs before using them.
   bool doNotSwap = true;
   for (int i = 0; i < arcs.size(); i++){
      DualSBox aOne = doNotSwap ? arcOne : arcTwo;
      DualSBox aTwo = doNotSwap ? arcTwo : arcOne;
      arcs[i]->draw(glu, mainBox, aOne, aTwo.first->getTextureID(), aTwo.second->getTextureID());
      doNotSwap = !doNotSwap;
   }
   // See if the player has an arc that needs to be drawn now.
   if (player == nullptr) return doNotSwap;
   PlayerAbility* pA = ((Player *)player)->getAbility();
   if (pA == nullptr || pA->getArc() == nullptr) return doNotSwap;
   // Draw it now.
   DualSBox aOne = doNotSwap ? arcOne : arcTwo;
   DualSBox aTwo = doNotSwap ? arcTwo : arcOne;
   pA->getArc()->draw(glu, mainBox, aOne, aTwo.first->getTextureID(), aTwo.second->getTextureID());
   // Does the swap and the return.
   return !doNotSwap;
}

void Level::drawShaderboxes(GLUtil* glu, Instance* player, int drewArcs, ShaderBox* screen){
   bool beforeArc = drewArcs == 0;
   bool replaceArc = drewArcs == 1;
   // Make sure we're drawing our shaderboxes first.
   if (!createdShaderboxes){
      shades = createShaderBoxes(glu);
      createdShaderboxes = true;
   }
   // Draw everything to each of the shader boxes, then draw that shaderbox.
   for (int i = 0; i < shades.size(); i++){
      ShaderBox* shade = shades[i];
      bool drawThisBox1 = beforeArc && shade->getDrawBeforeArc();
      bool drawThisBox2 = replaceArc && shade->getReplaceWithArc();
      bool drawThisBox3 = drewArcs > 1 && (!shade->getDrawBeforeArc() && !shade->getReplaceWithArc());
      bool drawThis = drawThisBox1 || drawThisBox2 || drawThisBox3;
      if (!(shade->canDraw()) || screen == nullptr || !drawThis) continue;
      shade->drawOnBox();
      // Draw to the background first.
      drawLayer(glu, LAYER_BACK);
      if (shade->getFastDraw()){
         // Optimize the drawing by just drawing what's on the screen at this point.
         screen->draw();
      } else {
         // Go through all of the drawing code that would normally be done for one layer.
         fullDraw(glu, player, drewArcs > 1, shade);
      }
      shade->drawOutBox();
      shade->draw();
   }
}

void Level::fullDraw(GLUtil* glu, Instance* player, bool drewArcs, ShaderBox* shade){
   std::map<int, Layer*>::iterator lI = layers.begin();
   bool drawnPlayer = false;
   while (lI != layers.end()){
      if (player != nullptr){
         // If the player is at this layer or an earlier layer, draw it here.
         std::vector<int> pLayers = player->getLayers();
         if (!drawnPlayer && pLayers.size() > 0 && lI->first >= pLayers[0]){
            drawnPlayer = true;
            if (player != nullptr){
               double cX = glu->draw->camX;
               double cY = glu->draw->camY;
               double wid = glu->draw->getWidth();
               double hei = glu->draw->getHeight();
               if (player->x < cX+wid && player->x+player->w > cX && player->y < cY+hei && player->y+player->h > cY){
                  player->draw(glu, lI->first);
               }
            }
         }
      }
      // Draw objects at this layer.
      drawObjects(glu, lI->first, 0);
      lI++;
   }
   if (drewArcs){
      // Note: We're still drawing to shade given how drawOnBox works.
      /// TODO: Do drawing arc code. 
      shade->clearArcBoxes();
      std::string dID = shade->getDrawID();
      shade->changeShader("", "arc");
      DualSBox aOne = (DualSBox){shade->getArcOne(), shade->getArcOneA()};
      DualSBox aTwo = (DualSBox){shade->getArcTwo(), shade->getArcTwoA()};
      bool drawTwo = drawArcs(glu, shade, aOne, aTwo, player);
      shade->changeShader(dID);
      // shade->changeShader("", "");
      // If this is a long shaderbox, this resets the uniform value for x.
      shade->resetUniforms();
      DualSBox drawMe = drawTwo ? aTwo : aOne;
      // Redraw to shade now that we're done using it.
      // Actually draw the arcs to the shaderbox here.
      drawMe.first->addUniformI("alphaTex", 1);
      glu->draw->bindTexture(drawMe.second->getTextureID(), 1);
      drawMe.first->draw();
   }
}

void Level::updateLevel(double deltaTime, Instance* player){
}

void Level::drawObjects(GLUtil* glu, int layer, int mode){
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   double cX = glu->draw->camX;
   double cY = glu->draw->camY;
   std::map<int, Layer*>::iterator lI = layers.find(layer);
   if (lI == layers.end()) return;
   Layer* l = layers.at(layer);
   if (l == nullptr || l->first == nullptr) return;
   for (DrawnInstance* d = l->first; d != nullptr; d = d->next){
      Instance* in = d->i;
      // Check if the instance is in the bounds of the screen.
      if (in->x < cX+wid && in->x+in->w > cX && in->y < cY+hei && in->y+in->h > cY){
         in->draw(glu, layer);
      } 
   }
}

bool Level::moveInstance(Instances* move, Level* otherLev){
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
   // Finally, we need to move the drawn instances over.
   bool changeLayers = removeFromLayers(move);
   changeLayers = otherLev->addToLayers(move) || changeLayers;
   return changeLayers;
}

bool Level::moveOutOfBounds(void* lv){
   LevelList* lev = (LevelList *)lv;
   if (lev == nullptr) return false;
   // For now, this is a simple out of bounds checker.
   bool ret = false;
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
                  ret = moveInstance(i, level) || ret;
                  break;
               }
            }
         }
      }
      i = next;
   }
   // TODO(?): Greedy checker to see if an object from an enclosing room has fallen into bounds.
   return ret;
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
   // Arcs are like instances, so move them like that.
   for (int i = 0; i < arcs.size(); i++){
      Arc* a = arcs[i];
      double X = a->getX();
      double Y = a->getY();
      if (horizontal && X-xOff >= splitLocation){
         a->setPosition(X+offset, Y);
         if (a->getX()-xOff < splitLocation) a->setPosition(splitLocation+xOff, Y);
      } else if (!horizontal && Y-yOff >= splitLocation){
         a->setPosition(X, Y+offset);
         if (a->getY()-yOff < splitLocation) a->setPosition(X, splitLocation+yOff);
      }
   }
   // Since camera objects deal with camera stuff, there may be some interesting behaviors.
   // These probably need to be accounted for.
   for (int i = 0; i < camObjs.size(); i++){
      camObjs[i]->bisectObject(horizontal, splitLocation, offset);
   }
   /// TODO: Add stuff for shaderboxes?

}

std::map<int, std::vector<Layer *>> Level::getLayers(std::map<int, std::vector<Layer *>> prevLayers){
   std::map<int, Layer *>::iterator layerIt = layers.begin();
   for (; layerIt != layers.end(); layerIt++){
      std::map<int, std::vector<Layer *>>::iterator it = prevLayers.find(layerIt->first);
      if (it == prevLayers.end()){
         std::vector<Layer *> l;
         l.push_back(layerIt->second);
         prevLayers.insert({layerIt->first, l});
      } else {
         prevLayers.at(layerIt->first).push_back(layerIt->second);
      }
   }
   return prevLayers;
}

bool Level::addToLayers(Instances* in){
   Instance* inst = in->i;
   std::vector<int> instLayers = inst->getLayers();
   bool addedALayer = false;
   for (int i = 0; i < instLayers.size(); i++){
      int layer = instLayers[i];
      std::map<int, Layer *>::iterator it = layers.find(layer);
      DrawnInstance* dI = new DrawnInstance();
      dI->i = inst;
      dI->prev = nullptr;
      dI->next = nullptr;
      dI->layer = layer;
      in->drawn.push_back(dI);
      if (it == layers.end()){
         // If there is no layer, make one with this instance.
         layers.insert({layer, new (Layer){this, dI, dI}});
         addedALayer = true;
      } else{
         Layer* l = layers.at(layer);
         // Put at the end of this drawing layer.
         l->last->next = dI;
         dI->prev = l->last;
         l->last = dI;
      }
   }
   return addedALayer;
}

bool Level::removeFromLayers(Instances* in){
   bool removedALayer = false;
   for (int i = 0; i < in->drawn.size(); i++){
      DrawnInstance* dI = in->drawn[i];
      std::map<int, Layer*>::iterator lI = layers.find(dI->layer);
      if (lI == layers.end()) continue;
      Layer* l = layers.at(dI->layer);
      // Update the layer if we no longer have something at the beginning or the end of the list.
      // Otherwise, keep the linked list connected.
      if (dI->prev == nullptr){
         assert(dI == l->first);
         l->first = dI->next;
      } else dI->prev->next = dI->next;
      if (dI->next == nullptr){
         assert(dI == l->last);
         l->last = dI->prev;
      } else dI->next->prev = dI->prev;
      // If there's nothing in the layer anymore, remove it.
      if (dI->prev == nullptr && dI->next == nullptr){
         layers.erase(dI->layer);
         removedALayer = true;
         delete l;
      }
      delete dI;
   }
   in->drawn.clear();
   return removedALayer;
}

BasicLevel::BasicLevel(std::string fName, double pX, double pY) : Level(){
   filePath = fName;
   playerX = pX;
   playerY = pY;
   // The width and height need to be known for level making purposes
   // So generate the level to get the width/height and then destroy it!
   setWidthHeight();
}

std::vector<Instance *> BasicLevel::makeLevel(std::vector<Instance*> previous){
   previous.push_back(new Player(playerX, playerY));
   return previous;
}
