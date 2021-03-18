#include "abilities.h"

AbilityHandler::AbilityHandler() : Instance(0, 0, 0, 0){
    head = nullptr;
    tail = nullptr;
    selected = nullptr;
    added = false;
}

void AbilityHandler::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    bool changedSelected = false;
    if (added){
        selected = tail;
        changedSelected = true;
        added = false;
    }
    if (keyPressed[BUTTON_SELECT] && selected != nullptr){
        selected = selected->next;
        if (selected == nullptr) selected = head;
        changedSelected = true;
    }
    if (selected != nullptr && changedSelected){
        ((Player *)player)->giveAbility((PlayerAbility*)(selected->i));
    }
}

void AbilityHandler::draw(GLDraw* gld, GLShaders* gls, int layer){
    // Do regular HUD drawing...
    if (selected == nullptr || selected->i == nullptr) return; 
    // Draw the selected ability.
    int tID = selected->i->texID();
    gld->enableTextures();
    if (tID != -1) gld->bindTexture(tID);
    gld->begin("QUADS");
    float hudX = gld->getWidth()-96;
    float hudY = 16;
    gld->texCoords(0, 0);
    gld->vertW(hudX, hudY);
    gld->texCoords(0, 1);
    gld->vertW(hudX, hudY+32);
    gld->texCoords(1, 1);
    gld->vertW(hudX+32, hudY+32);
    gld->texCoords(1, 0);
    gld->vertW(hudX+32, hudY);
    gld->end();
    if (tID != -1) gld->bindTexture(0);
    gld->disableTextures();
    // Some abilities have HUD sections that need to be drawn themselves.
    ((PlayerAbility*)(selected->i))->drawHUD(gld, gls);
}

void AbilityHandler::addAbility(PlayerAbility* ability){
    /// Adds the new ability to the end of the list.
    Instances* newAbility = new Instances();
    newAbility->i = ability;
    newAbility->prev = tail;
    if (head != nullptr){
        tail->next = newAbility;
    } else{
        head = newAbility;
        tail = newAbility;
    }
    tail = newAbility;
    added = true;
}
