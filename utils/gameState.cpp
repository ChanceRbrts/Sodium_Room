#include "gameState.h"

std::map<std::string, saveVar> GameState::stateMap = emptyMap();

std::map<std::string, saveVar> GameState::emptyMap(){
    std::map<std::string, saveVar> retMap;
    return retMap;
}
