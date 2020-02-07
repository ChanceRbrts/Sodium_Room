#include "gameLogic.h"

GameLogic::GameLogic(){
   levels = new Levels();
   currentLevel = levels->lev[2];
   head = nullptr;
   madeBoxes = false;
   createdFonts = false;
   loadLevel();
}

GameLogic::~GameLogic(){
   FontBook::destroy();
}

void GameLogic::loadLevel(){
   /*head = addToList(nullptr, new Solid(5,10));
   addToList(head, new Player(5, 3));
   */
   
   // Get the instance list and turns it into a linked list.
   std::vector<Instance *> insts = currentLevel->createLevel();
   bool headIsNull = true;
   Instances* last = nullptr;
   hud = new Instances();
   lastHud = hud;
   for (int i = 0; i < insts.size(); i++){
      // printf("%f, %f\n", insts[i]->x, insts[i]->y);
      last = addToList(last, insts[i]);
      if (insts[i]->isPlayer()) player = insts[i];
      if (headIsNull) head = last;
      headIsNull = false;
   }
   /*
   // Start of Removal.
   // This is just a test for a text box.
   // This will be removed later.
   std::vector<std::string> lines;
   lines.push_back("???: |font:Times New Roman|Hey `|color:0000ff|#name|color:000000|` nice to meet ya... Did you know you don't have an extension? Or permissions for that matter... You don't even belong to a user! Are you a |color:ff0000|virus|color:000000|?");
   lastHud = addToList(lastHud, new TextBox(lines));
   // End of Removal
   */
   madeBoxes = false;
}

void GameLogic::createShaderBoxes(GLUtil* glu){
   // shaderboxes.push_back(new ShaderBox(0, 0, 10, 15, "", "testShader", glu));
   shaderboxes = currentLevel->createShaderBoxes(glu);
}

void GameLogic::update(double deltaTime, GLUtil* glu){
   // Key our controls.
   bool* keyPressed = glu->control->getKeyPressed();
   bool* keyHeld = glu->control->getKeyHeld();
   if (keyPressed[BUTTON_END]) exit(0);
   // Update each of the objects.
   if (head != nullptr){
      for (Instances* i = head; i != nullptr; i = i->next){
         // Update with the player.
         i->i->upd(deltaTime, keyPressed, keyHeld, player);
         // If an object is destroyed, destroy it.
         if (i->i->canRemove()){
            i = i->prev;
            removeFromList(i->next);
         }
      }
      // Collision
      for (int cCorners = 0; cCorners < 2; cCorners++){
         for (Instances* i = head; i != nullptr; i = i->next){
            Instance* in = i->i;
            if (i->next != nullptr){
               for (Instances* j = head->next; j != nullptr; j = j->next){
                  in->collision(j->i, deltaTime, cCorners > 0);
               }
            }
         }
      }
      // Change positions here, basically.
      for (Instances* i = head; i != nullptr; i = i->next){
         i->i->finishUpdate(deltaTime);
         // If an object has a few objects that it needs to add, add them to the list.
         if (i->i->toAdd.size() > 0){
            for (int j = 0; j < i->i->toAdd.size(); j++){ 
               addToList(i, i->i->toAdd[j]);
            }
            i->i->toAdd.clear();
         }
      }
   }
   // Update the camera.
   followPlayer(glu);
   // Update the shaderboxes that need updating.
   for (int i = 0; i < shaderboxes.size(); i++){
      shaderboxes[i]->moveShaderBox(player->x+player->w/2, player->y+player->h/2);
   }
   // Update the HUD
   if (hud != nullptr && hud->next != nullptr){
      for (Instances* i = hud->next; i != nullptr; i = i->next){
         i->i->update(deltaTime, keyPressed, keyHeld);
         if (i->i->canRemove()){
            i = i->prev;
            removeFromList(i->next);
         }
      }
   }
   // Make sure pressed keys are no longer marked as pressed.
   glu->control->resetControls();
}

void GameLogic::followPlayer(GLUtil* glu){
   // Very simple following the player code; Might be changed later?
   double cX = player->x+player->w/2-glu->draw->getWidth()/2;
   double cY = player->y+player->h/2-glu->draw->getHeight()/2;
   if (cX > 32*currentLevel->w-glu->draw->getWidth()){
      cX = 32*currentLevel->w-glu->draw->getWidth();
   } 
   if (cY > 32*currentLevel->h-glu->draw->getHeight()){
      cY = 32*currentLevel->h-glu->draw->getHeight();
   }
   if (cX < 0) cX = 0;
   if (cY < 0) cY = 0;
   glu->draw->camX = cX;
   glu->draw->camY = cY;
}

void GameLogic::draw(GLUtil* glu){
   // Make textures for default fonts here.
   if (!createdFonts){
      FontBook::initialize(glu);
      FontBook::loadFont("Courier New");
      createdFonts = true;
   }
   // TODO: Add support for multiple levels.
   currentLevel->draw(glu, player);
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

void GameLogic::drawObjects(GLUtil* glu, int mode){
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   double cX = glu->draw->camX;
   double cY = glu->draw->camY;
   if (head != nullptr){
      for (Instances* i = head; i != nullptr; i = i->next){
         Instance* in = i->i;
         // Check if the instance is in the bounds of the screen.
         if (in->x < cX+wid && in->x+in->w > cX && in->y < cY+hei && in->y+in->h > cY){
            in->draw(glu);
         }
      }
   }
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
void GameLogic::removeFromList(Instances* i){
   Instances* prev = i->prev;
   Instances* next = i->next;
   if (prev != nullptr) prev->next = next;
   if (next != nullptr) next->prev = prev;
   delete i->i;
   delete i;
}