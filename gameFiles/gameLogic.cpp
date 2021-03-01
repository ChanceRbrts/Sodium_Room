#include "gameLogic.h"

GameLogic::GameLogic(){
   levels = new Levels();
   createdFonts = false;
   loadedCam = false;
   loadedLevels = nullptr;
   player = nullptr;
   camera = new Camera();
   reloadLayers = false;
   drawBox = nullptr;
   arcBoxOne = (DualSBox){nullptr, nullptr};
   arcBoxTwo = (DualSBox){nullptr, nullptr};
   curSMapID = 0;
   /// TODO: Width and height hardcoded; Fix that.
   loadSuperMap(MAP_MAIN, 0, 0, 640, 480);
}

GameLogic::~GameLogic(){
   FontBook::destroy();
   TexBook::destroy();
}

void GameLogic::loadSuperMap(int mapID, double X, double Y, double W, double H){
   curSMapID = mapID;
   pairVector<Map*> pV = levels->getSuperMap(mapID, X, Y, W, H);
   // Make it so we have our supermap ready to load stuff!
   superMap = pV.a;
   for (int i = 0; i < pV.b.size(); i++){
      std::vector<Level *> lev = pV.b[i]->updateLoadedLevels(X, Y, W, H);
      for (int j = 0; j < lev.size(); j++){
         loadLevel(lev[j], pV.b[i]);
      }
   }
}

void GameLogic::loadLevel(Level* l, Map* m){
   // Get the instance list and turns it into a linked list.
   pointDouble playerLoc = l->createLevel();
   if (player == nullptr){
      player = new Player(playerLoc.x/32, playerLoc.y/32);
   }
   LevelList* lev = new LevelList();
   lev->lev = l;
   lev->map = m;
   lev->prev = nullptr;
   lev->next = nullptr;
   if (loadedLevels == nullptr){
      loadedLevels = lev;
   } else {
      lastLoaded->next = lev;
      lev->prev = lastLoaded;
   }
   lastLoaded = lev;
   if (hud == nullptr){
      hud = new Instances();
      hud->next = nullptr;
      hud->prev = nullptr;
      hud->i = nullptr;
      AbilityHandler* aHandler = new AbilityHandler();
      /// TODO: Find a better home for this.
      aHandler->addAbility(new Lighter());
      aHandler->addAbility(new Flashlight());
      lastHud = hud;
      lastHud = addToList(lastHud, aHandler);
   }
   reloadLayers = true;
   /*
   // Start of Removal.
   // This is just a test for a text box.
   // This will be removed later.
   std::vector<std::string> lines;
   lines.push_back("???: |font:Times New Roman|Hey `|color:0000ff|#name|color:000000|` nice to meet ya... Did you know you don't have an extension? Or permissions for that matter... You don't even belong to a user! Are you a |color:ff0000|virus|color:000000|?");
   lastHud = addToList(lastHud, new TextBox(lines));
   // End of Removal
   */
}

void GameLogic::unloadLevel(LevelList* l){
   // Check to see if any instance in the level needs to do some mess cleanup first.
   for (Instances* in = l->lev->insts; in != nullptr; in = in->next){
      Instance* i = in->i;
      if (i->canMessWithLevel()){
         InstanceLev* iL = (InstanceLev*)i;
         reloadLayers = iL->removeMessFromWorld(loadedLevels, l->lev, player) || reloadLayers;
      }
   }
   // Remove stuff from the level.
   l->lev->destroyLevel();
   if (l->prev != nullptr) l->prev->next = l->next;
   if (l->next != nullptr) l->next->prev = l->prev;
   if (loadedLevels == l) loadedLevels = l->next;
   if (lastLoaded == l) lastLoaded = l->prev;
   reloadLayers = true;
   // We don't want to actually deallocate the level here.
   delete l;
}

void GameLogic::modifyLevelsLoaded(GLUtil* glu){
   // For now, let's have a level loaded in if it is within a screen's length away from the screen.
   double cX = glu->draw->camX;
   double cY = glu->draw->camY;
   double w = glu->draw->getWidth();
   double h = glu->draw->getHeight();
   double minX = cX-w;
   double minY = cY-h;
   double maxX = cX+2*w;
   double maxY = cY+2*w;
   // First, deallocate the levels that are out of bounds.
   /// TODO: Enclosed levels still break this when expanded past the breaking point.
   LevelList* l = loadedLevels;
   while (l != nullptr){
      Level* lev = l->lev;
      bool remove = false;
      double lX = lev->getXOff();
      double lY = lev->getYOff();
      remove = lX+lev->w < minX || lX > maxX;
      remove = remove || lY+lev->h < minY || lY > maxY;
      LevelList* lNext = l->next;
      if (remove && !lev->getGlobal()){
         unloadLevel(l);
      }
      l = lNext;
   }
   // Now, check for levels that are in bounds and load them in.
   for (int i = 0; i < superMap.size(); i++){
      if (!superMap[i]->inBounds(cX-w*3/4, cY-h*3/4, w*5/2, h*5/2)) continue;
      std::vector <Level *> levs = superMap[i]->updateLoadedLevels(glu);
      for (int j = 0; j < levs.size(); j++){
         loadLevel(levs[j], superMap[i]);
      }
      levs.clear();
   }
}

void GameLogic::update(double deltaTime, GLUtil* glu){
   // printf("%f\n", 1/deltaTime);
   // Key our controls.
   bool* keyPressed = glu->control->getKeyPressed();
   bool* keyHeld = glu->control->getKeyHeld();
   if (keyPressed[BUTTON_END]) exit(0);
   modifyLevelsLoaded(glu);
   // Update each of the objects.
   // collObjs is used for collision checking.
   // immovableColl is for solid objects that won't move.
   // These need to be checked for collision first.
   std::vector<Instance *> collObjs;
   std::vector<Instance *> immovableColl;
   Arc* pAr = nullptr;
   if (player != nullptr){ 
      player->upd(deltaTime, keyPressed, keyHeld, player);
      collObjs.push_back(player);
      if (player->getName().compare("Player") == 0){
         PlayerAbility* pA = ((Player *)player)->getAbility();
         if (pA != nullptr) pAr = pA->getArc();
      }
   }
   int levID = 0;
   LevelList* lList = loadedLevels;
   // Get a list of all the arcs in the level.
   std::vector<Arc *> arcs;
   while (lList != nullptr){
      Level* l = lList->lev;
      for (int i = 0; i < l->arcs.size(); i++){
         arcs.push_back(l->arcs[i]);
      }
      lList = lList->next;
   }
   lList = loadedLevels;
   while (lList != nullptr){
      Level* l = lList->lev;
      l->updateLevel(deltaTime, player);
      // The player can be affected by one of the arcs in this level.
      for (int a = 0; a < l->arcs.size(); a++){
         player->arcCol(l->arcs[a], deltaTime, a+levID);
      }
      Instances* in = l->insts;
      while (in != nullptr){
         in->i->upd(deltaTime, keyPressed, keyHeld, player);
         Instances* next = in->next;
         // All arcs loaded in need to be tested with the instance.
         // However, since not many levels will be loaded at once, this should be fine?
         // It also helps that arc collisions aren't intensive if there's no way 
         // the arc will ever collide with the instance.
         if (pAr != nullptr) in->i->arcCol(pAr, deltaTime, -1);
         for (int a = 0; a < arcs.size(); a++){
            // levID has already been accounted for with the full arc values, so it doesn't need to be included.
            in->i->arcCol(arcs[a], deltaTime, a);
         }
         // If an instance can mess with the levels, allow it here.
         if (in->i->canMessWithLevel()){
            InstanceLev* iL = (InstanceLev *)(in->i);
            reloadLayers =  
               iL->messWithLevels(loadedLevels, lList->lev, lList->map, player) || reloadLayers;
         }
         // If an object is destroyed, destroy it.
         if (in->i->canRemove()){
            Instances* toRemove = in;
            reloadLayers = l->removeFromLayers(toRemove) || reloadLayers;
            removeFromList(toRemove, &(l->insts));
         } else{
            if (in->i->isImmovable()) immovableColl.push_back(in->i);
            else collObjs.push_back(in->i);
         }
         in = next;
      }
      levID += l->arcs.size();
      // The last loaded level could change depending on some game objects messing with levels.
      if (lList->next == nullptr) lastLoaded = lList;
      lList = lList->next;
   }
   // Collision
   // Run this loop twice, one without checking corners, and one with.
   for (int cCorners = 0; cCorners < 2; cCorners++){
      for (int i = 0; i < collObjs.size(); i++){
         Instance* in = collObjs[i];
         // Check the immovable solid objects first.
         for (int j = 0; j < immovableColl.size(); j++){
            in->collision(immovableColl[j], deltaTime, cCorners > 0);
         }
         // Do a collision check!
         for (int j = i+1; j < collObjs.size(); j++){
            in->collision(collObjs[j], deltaTime, cCorners > 0);
         }
         // Only do a collision with the map gaps AFTER colliding with the rest of the instances.
         if (cCorners == 1){
            Map::collideGapWithInstance(in, deltaTime, true);
            Map::collideGapWithInstance(in, deltaTime, false);
         }
      }
   }
   collObjs.clear();
   immovableColl.clear();
   // Finish the Update Loop (Change position here, basically.)
   lList = loadedLevels;
   if (player != nullptr) player->finishUpdate(deltaTime);
   while (lList != nullptr){
      Level* l = lList->lev;
      Instances* in = l->insts;
      while (in != nullptr){
         in->i->finishUpdate(deltaTime);
         // Add objects that may have been added by our object.
         if (in->i->toAdd.size() > 0){
            for (int i = 0; i < in->i->toAdd.size(); i++){
               Instances* newInst = addToList(in, in->i->toAdd[i]);
               reloadLayers = l->addToLayers(newInst) || reloadLayers;
            }
            in->i->toAdd.clear();
         }
         in = in->next;
      }
      lList = lList->next;
   }
   // Finally, make sure instances are in their right levels!
   lList = loadedLevels;
   while (lList != nullptr){
      reloadLayers = lList->lev->moveOutOfBounds(loadedLevels) || reloadLayers;
      lList = lList->next;
   }
   arcs.clear();
   // Update the camera.
   updateCamera(deltaTime, glu);
   // Update the shaderboxes that need updating.
   if (loadedLevels != nullptr){
      for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
         for (int i = 0; i < l->lev->shades.size(); i++){
            if (l->lev->shades[i]->followPlayer()){
               GLDraw* gld = glu->draw;
               l->lev->shades[i]->moveShaderBox(gld->camX+gld->getWidth()/2, 
                                                gld->camY+gld->getHeight()/2, false);
            }
         }
      }
   }
   // Update the HUD
   if (hud != nullptr && hud->next != nullptr){
      for (Instances* i = hud->next; i != nullptr; i = i->next){
         i->i->update(deltaTime, keyPressed, keyHeld, player);
         if (i->i->canRemove()){
            i = i->prev;
            removeFromList(i->next, &hud);
         }
      }
   }
   // Make sure pressed keys are no longer marked as pressed.
   glu->control->resetControls();
}

void GameLogic::updateCamera(double deltaTime, GLUtil* glu){
   // Start by getting the target of the camera.
   if (player != nullptr){
      pointDouble pD = followPlayer(deltaTime, glu);
      if (!loadedCam){
         if (loadedLevels != nullptr){
            for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
               Level* lev = l->lev;
               double xO = lev->getXOff();
               double yO = lev->getYOff();
               if (pD.x >= xO && pD.x < xO+lev->w && pD.y >= yO && pD.y < yO+lev->h){
                  camera->setPosition(xO, yO);
               }
            }
         } else camera->setPosition(pD.x, pD.y);
      }
      camera->setTarget(pD.x, pD.y);
   }
   camera->startMovement(deltaTime);
   // Then, constrain it to different parts of the levels.
   if (loadedLevels != nullptr){
      for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
         std::vector<CameraObject*> cO = l->lev->camObjs;
         double wid = glu->draw->getWidth();
         double hei = glu->draw->getHeight();
         for (int i = 0; i < cO.size(); i++){
            cO[i]->modifyCamera(camera, deltaTime, wid, hei);
         }
      }
   }
   // Finally, update the camera positon.
   camera->finishMovement(deltaTime, loadedCam);
   loadedCam = true;
   glu->draw->camX = camera->getX();
   glu->draw->camY = camera->getY();
}

pointDouble GameLogic::followPlayer(double deltaTime, GLUtil* glu){
   double camX = camera->getX()+((Player*)player)->getCamJumpX();
   double camY = camera->getY()+((Player*)player)->getCamJumpY();
   camera->setPosition(camX, camY);
   // Very simple following the player code; Might be changed later?
   double cX = player->x+player->w/2-glu->draw->getWidth()/2;
   double cY = player->y+player->h/2-glu->draw->getHeight()/2;
   double minX = 0;
   double maxX = 0;
   double minY = 0;
   double maxY = 0;
   // You know what? Let's just have a whole bunch of std::mins and std::maxs here to avoid a ton of conditionals.
   if (loadedLevels != nullptr){
      double W = glu->draw->getWidth();
      double H = glu->draw->getHeight();
      for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
         double xOff = l->lev->getXOff();
         double yOff = l->lev->getYOff();
         double xVal = l->lev->getXOff()+l->lev->w-W;
         double yVal = l->lev->getYOff()+l->lev->h-H;
         minX = std::min(minX, xOff);
         maxX = std::max(maxX, xVal);
         minY = std::min(minY, yOff);
         maxY = std::max(maxY, yVal);
         // While we're here, let's affect the camera objects.
         for (int i = 0; i < l->lev->camObjs.size(); i++){
            pointDouble newCs = l->lev->camObjs[i]->interactWithPlayer(cX, cY, W, H, player, deltaTime);
            cX = newCs.x;
            cY = newCs.y;
         }
      }
   }
   cX = std::max(minX, std::min(cX, maxX));
   cY = std::max(minY, std::min(cY, maxY));
   return (pointDouble){cX, cY, 0};
}

void GameLogic::draw(GLUtil* glu){
   if (reloadLayers){
      layers = generateLayers();
      reloadLayers = false;
   }
   // Make textures for default fonts here.
   if (!createdFonts){
      FontBook::initialize(glu);
      FontBook::loadFont("Courier New");
      createdFonts = true;
   }
   GLDraw* gld = glu->draw;
   // Create our shaderboxes to draw to the screen.
   if (drawBox == nullptr){
      drawBox = new ShaderBox(0, 0, gld->getWidth()/32, gld->getHeight()/32, "", "", glu);
      // The "first" of these pairs represent the colors.
      // The "second" of these paris represent the opaqueness.
      arcBoxOne.first = new ShaderBox(0, 0, gld->getWidth()/32, gld->getHeight()/32, "", "drawArc", glu);
      arcBoxOne.second = new ShaderBox(0, 0, gld->getWidth()/32, gld->getHeight()/32, "", "", glu);
      arcBoxTwo.first = new ShaderBox(0, 0, gld->getWidth()/32, gld->getHeight()/32, "", "drawArc", glu);
      arcBoxTwo.second = new ShaderBox(0, 0, gld->getWidth()/32, gld->getHeight()/32, "", "", glu);
   }
   drawBox->moveShaderBox(gld->camX, gld->camY, false);
   arcBoxOne.first->moveShaderBox(gld->camX, gld->camY, false);
   arcBoxOne.second->moveShaderBox(gld->camX, gld->camY, false);
   arcBoxTwo.first->moveShaderBox(gld->camX, gld->camY, false);
   arcBoxTwo.second->moveShaderBox(gld->camX, gld->camY, false);
   if (loadedLevels == nullptr) return;
   drawBox->drawOnBox();
   // Draw the backgrounds first.
   for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
      l->lev->drawLayer(glu, LAYER_BACK);
   }
   // Draw the layers of the objects.
   std::map<int, std::vector<Layer *>>::iterator dI = layers.begin();
   for (; dI != layers.end(); dI++){
      for (int i = 0; i < dI->second.size(); i++){
         if (dI->second[i] == nullptr){
            // If a layer is a nullptr, assume it belongs to the game logic, and is thus the player.
            if (player != nullptr){
               double cX = glu->draw->camX;
               double cY = glu->draw->camY;
               double wid = glu->draw->getWidth();
               double hei = glu->draw->getHeight();
               if (player->x < cX+wid && player->x+player->w > cX && player->y < cY+hei && player->y+player->h > cY){
                  player->draw(glu, dI->first);
                  PlayerAbility* pA = ((Player*)player)->getAbility();
                  if (pA != nullptr) pA->draw(glu, dI->first);
               }
            }
         } else{
            dI->second[i]->lev->drawLayer(glu, dI->first);
         }
      }
   }
   // Draw the shaderboxes that should be drawn before the arc.
   for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
      l->lev->drawShaderboxes(glu, player, 0, drawBox);
   }
   bool drawOne = true;
   // Reset arcOne's alpha values by drawing a black transparent rectangle on it.
   arcBoxOne.second->drawOnBox();
   arcBoxOne.second->clearBox();
   arcBoxOne.second->drawOutBox();
   arcBoxTwo.second->drawOnBox();
   arcBoxTwo.second->clearBox();
   arcBoxTwo.second->drawOutBox();
   drawBox->changeShader("", "arc");
   // Now, draw the arcs.
   for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
      DualSBox aOne = drawOne ? arcBoxOne : arcBoxTwo;
      DualSBox aTwo = drawOne ? arcBoxTwo : arcBoxOne;
      // Draw the player ability last, so pass in nullptr if this isn't the final level.
      Instance* possPlay = l->next == nullptr ? player : nullptr;
      bool dontSwap = l->lev->drawArcs(glu, drawBox, aOne, aTwo, possPlay);
      drawOne ^= !dontSwap;
   }
   drawBox->changeShader("");
   // Before drawing the arcs, there are a few shaderboxes that need to be drawn first.
   for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
      l->lev->drawShaderboxes(glu, player, 1, drawBox);
   }
   DualSBox drawMe = drawOne ? arcBoxTwo : arcBoxOne;
   // printf("%d\n", drawMe.second->getTextureID());
   drawMe.first->addUniformI("alphaTex", 1);
   gld->bindTexture(drawMe.second->getTextureID(), 1);
   drawMe.first->draw();
   drawBox->drawOutBox();
   drawBox->draw();
   // Draw the shaderboxes next.
   for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
      l->lev->drawShaderboxes(glu, player, 2, drawBox);
   }
   // Finally, draw the gaps in the map to finish it off!
   Map::drawGaps(glu);
   // We want the HUD to be static on the screen.
   gld->pushCameraMem(0, 0, gld->getWidth(), gld->getHeight());
   if (hud != nullptr && hud->next != nullptr){
      for (Instances* i = hud->next; i != nullptr; i = i->next){
         if (i->i == nullptr) return;
         i->i->draw(glu, 0);
      }
   }
   gld->popCameraMem();
}

std::map<int, std::vector<Layer *>> GameLogic::generateLayers(){
   layers.clear();
   // Since the player is with the Game Logic, there is no layer that it's a part of.
   if (player != nullptr){
      std::vector<int> pLayers = player->getLayers();
      for (int i = 0; i < pLayers.size(); i++){
         std::vector<Layer*> l;
         l.push_back(nullptr);
         layers.insert({pLayers[i], l});
      }
   }
   if (loadedLevels == nullptr) return layers;
   for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
      // Get the layers to be drawn to by the level here.
      layers = l->lev->getLayers(layers);
   }
   return layers;
}

/**
 * Simple adding to a linked list.
 * */
Instances* GameLogic::addToList(Instances* prev, Instance* i){
   Instances* in = new Instances();
   in->i = i;
   in->prev = prev;
   in->next = nullptr;
   if (prev != nullptr){
      Instances* next = prev->next;
      in->next = next;
      prev->next = in;
      if (next != nullptr){
         next->prev = in;
      }
   }
   return in;
}

/**
 * Yeah, this is just a pretty simple double linked list removal.
 * */
void GameLogic::removeFromList(Instances* i, Instances** start){
   Instances* prev = i->prev;
   Instances* next = i->next;
   if (prev != nullptr) prev->next = next;
   if (next != nullptr) next->prev = prev;
   // Make sure we aren't removing the first thing in the linked list.
   if (*start == i) *start = i->next;
   if (i->i->canDeleteIfRemoved()){
      delete i->i;
   }
   delete i;
}