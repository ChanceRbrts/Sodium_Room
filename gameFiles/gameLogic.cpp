#include "gameLogic.h"

GameLogic::GameLogic(){
   levels = new Levels();
   createdFonts = false;
   loadedCam = false;
   loadedLevels = nullptr;
   player = nullptr;
   camera = new Camera();
   loadLevel(levels->lev[LEV_TEST_RAIN]);
}

GameLogic::~GameLogic(){
   FontBook::destroy();
   TexBook::destroy();
}

void GameLogic::loadLevel(Level* l){
   // Get the instance list and turns it into a linked list.
   pointDouble playerLoc = l->createLevel();
   if (player == nullptr){
      player = new Player(playerLoc.x/32, playerLoc.y/32);
      // TODO: Find a better place for this.
      ((Player *)player)->giveAbility(new Lighter());
      // ((Player *)player)->giveAbility(new Flashlight());
   }
   LevelList* lev = new LevelList();
   lev->lev = l;
   if (loadedLevels == nullptr){
      loadedLevels = lev;
   } else {
      lastLoaded->next = lev;
      lev->prev = lastLoaded;
   }
   lastLoaded = lev;
   hud = new Instances();
   lastHud = hud;
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
   // Remove stuff from the level.
   l->lev->destroyLevel();
   if (l->prev != nullptr) l->prev->next = l->next;
   if (l->next != nullptr) l->next->prev = l->prev;
   // We don't want to actually deallocate the level here.
   delete l;
}

void GameLogic::update(double deltaTime, GLUtil* glu){
   // Key our controls.
   bool* keyPressed = glu->control->getKeyPressed();
   bool* keyHeld = glu->control->getKeyHeld();
   if (keyPressed[BUTTON_END]) exit(0);
   // Update each of the objects.
   LevelList* lList = loadedLevels;
   // collObjs is used for collision checking.
   std::vector<Instance *> collObjs;
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
         // Levels have arcs that may collide with objects in there.
         if (pAr != nullptr) in->i->arcCol(pAr, deltaTime, -1);
         for (int a = 0; a < l->arcs.size(); a++){
            in->i->arcCol(l->arcs[a], deltaTime, a+levID);
         }
         // If an instance can mess with the levels, allow it here.
         if (in->i->canMessWithLevel()){
            InstanceLev* iL = (InstanceLev *)(in->i);
            iL->messWithLevels(loadedLevels, player);
         }
         // If an object is destroyed, destroy it.
         if (in->i->canRemove()){
            Instances* toRemove = in;
            removeFromList(toRemove, &(l->insts));
         } else collObjs.push_back(in->i);
         in = next;
      }
      levID += l->arcs.size();
      lList = lList->next;
   }
   // Collision
   // Run this loop twice, one without checking corners, and one with.
   for (int cCorners = 0; cCorners < 2; cCorners++){
      for (int i = 0; i < collObjs.size(); i++){
         Instance* in = collObjs[i];
         for (int j = i+1; j < collObjs.size(); j++){
            in->collision(collObjs[j], deltaTime, cCorners > 0);
         }
      }
   }
   collObjs.clear();
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
               addToList(in, in->i->toAdd[i]);
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
      lList->lev->moveOutOfBounds(loadedLevels);
      lList = lList->next;
   }
   // Update the camera.
   updateCamera(deltaTime, glu);
   // Update the shaderboxes that need updating.
   if (loadedLevels != nullptr){
      for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
         for (int i = 0; i < l->lev->shades.size(); i++){
            if (l->lev->shades[i]->followPlayer()){
               l->lev->shades[i]->moveShaderBox(player->x+player->w/2, player->y+player->h/2);
            }
         }
      }
   }
   // Update the HUD
   if (hud != nullptr && hud->next != nullptr){
      for (Instances* i = hud->next; i != nullptr; i = i->next){
         i->i->update(deltaTime, keyPressed, keyHeld);
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
      pointDouble pD = followPlayer(glu);
      if (loadedCam) camera->setTarget(pD.x, pD.y);
      else camera->setPosition(pD.x, pD.y);
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

pointDouble GameLogic::followPlayer(GLUtil* glu){
   // Very simple following the player code; Might be changed later?
   double cX = player->x+player->w/2-glu->draw->getWidth()/2;
   double cY = player->y+player->h/2-glu->draw->getHeight()/2;
   double minX = 0;
   double maxX = 0;
   double minY = 0;
   double maxY = 0;
   // You know what? Let's just have a whole bunch of std::mins and std::maxs here to avoid a ton of conditionals.
   if (loadedLevels != nullptr){
      for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
         double xVal = l->lev->getXOff()+l->lev->w-glu->draw->getWidth();
         double yVal = l->lev->getYOff()+l->lev->h-glu->draw->getHeight();
         minX = std::min(minX, (double)(l->lev->getXOff()));
         maxX = std::max(maxX, xVal);
         minY = std::min(minY, (double)(l->lev->getYOff()));
         maxY = std::max(maxY, yVal);
      }
   }
   cX = std::max(minX, std::min(cX, maxX));
   cY = std::max(minY, std::min(cY, maxY));
   return (pointDouble){cX, cY, 0};
}

void GameLogic::draw(GLUtil* glu){
   // Make textures for default fonts here.
   if (!createdFonts){
      FontBook::initialize(glu);
      FontBook::loadFont("Courier New");
      createdFonts = true;
   }
   if (loadedLevels != nullptr){
      for (LevelList* l = loadedLevels; l != nullptr; l = l->next){
         l->lev->draw(glu, player);
      }
   }
   // We want the HUD to be static on the screen.
   GLDraw* gld = glu->draw;
   gld->pushCameraMem(0, 0, gld->getWidth(), gld->getHeight());
   if (hud != nullptr && hud->next != nullptr){
      for (Instances* i = hud->next; i != nullptr; i = i->next){
         i->i->draw(glu);
      }
   }
   gld->popCameraMem();
}

/**
 * Simple adding to a linked list.
 * */
Instances* GameLogic::addToList(Instances* prev, Instance* i){
   Instances* in = new Instances();
   in->i = i;
   in->prev = prev;
   if (prev != nullptr){
      in->next = prev->next;
      prev->next = in;
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
   delete i->i;
   delete i;
}