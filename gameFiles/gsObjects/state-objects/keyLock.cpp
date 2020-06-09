#include "keyLock.h"

Key::Key(double X, double Y, std::string lock) : Instance(X, Y, 1, 1){
    name = "Key";
    lName = lock;
    remove = GameState::getSaveB(lock);
    colList.push_back("Player");
    GameState::setPermanent(lName, true);
}

Key::Key(double X, double Y, std::string lock, bool perm) : Instance(X, Y, 1, 1){
    name = "Key";
    lName = lock;
    remove = GameState::getSaveB(lock);
    colList.push_back("Player");
    if (perm) GameState::setPermanent(lName, true);
}

void Key::collided(Instance* o, double deltaTime){
    if (o->getName().compare("Player") != 0) return;
    // This is just a picked up item.
    // TODO: Add particle effects to this?
    remove = true;
    GameState::setSaveB(lName, true);
}
