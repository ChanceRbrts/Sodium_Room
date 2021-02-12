#include "abilities.h"

HUDAbilities::HUDAbilities() : Instance(0, 0, 0, 0){
    head = nullptr;
    tail = nullptr;
    selected = nullptr;
}

void HUDAbilities::update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
    if (keyPressed[BUTTON_SELECT] && selected != nullptr){
        selected = selected->next;
        if (selected == nullptr) selected = head;
        else ((Player *)player)->giveAbility((PlayerAbility*)(selected->i));
    }
}

void HUDAbilities::addAbility(PlayerAbility* ability){
    /// TODO: All of this.
}
