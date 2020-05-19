#include "gameState.h"

std::map<std::string, saveVar> GameState::stateMap = emptyMap();

std::map<std::string, saveVar> GameState::emptyMap(){
    std::map<std::string, saveVar> retMap;
    return retMap;
}

bool GameState::hasValue(std::string key){
    std::map<std::string, saveVar>::iterator it = stateMap.find(key);
    return it != stateMap.end();
}

/** TODO: Implement */
int GameState::loadFile(std::string fileName){
    
}

/** TODO: Implement */
int GameState::saveFile(std::string fileName){

}

int GameState::setPermanent(std::string key, bool toSave){
    bool hasval = hasValue(key);
    saveVar sV = hasval ? stateMap[key] : (saveVar){ toSave, SAV_ERR, 0.0 };
    sV.save = toSave;
    if (hasval) stateMap[key] = sV;
    else stateMap.insert({key, sV});
    return sV.type;
}

int GameState::getType(std::string key){
    if (!hasValue(key)) return SAV_ERR;
    saveVar sV = stateMap.at(key);
    return sV.type;
}

bool GameState::getSaveB(std::string key){
    if (!hasValue(key)) return false;
    saveVar sV = stateMap.at(key);
    if (sV.type == SAV_BOOL) return sV.data.b;
    if (sV.type == SAV_INT) return sV.data.i != 0;
    if (sV.type == SAV_DOUBLE) return (sV.data.d != 0);
    return false;
}

int GameState::getSaveI(std::string key){
    if (!hasValue(key)) return 0;
    saveVar sV = stateMap.at(key);
    if (sV.type == SAV_BOOL) return sV.data.b ? 1 : 0;
    if (sV.type == SAV_INT) return sV.data.i;
    if (sV.type == SAV_DOUBLE) return (int)(sV.data.d);
    return 0;
}

double GameState::getSaveD(std::string key){
    if (!hasValue(key)) return 0;
    saveVar sV = stateMap.at(key);
    if (sV.type == SAV_BOOL) return sV.data.b ? 1 : 0;
    if (sV.type == SAV_INT) return (double)(sV.data.i);
    if (sV.type == SAV_DOUBLE) return sV.data.d;
    return 0;
}

void GameState::setSaveB(std::string key, bool b){
    bool hasval = hasValue(key);
    bool toSave = hasval ? stateMap[key].save : false;
    saveVar sV = (saveVar){ toSave, SAV_BOOL, b };
    if (hasval) stateMap[key] = sV;
    else stateMap.insert({key, sV});
}

void GameState::setSaveI(std::string key, int i){
    bool hasval = hasValue(key);
    bool toSave = hasval ? stateMap[key].save : false;
    saveVar sV = (saveVar){ toSave, SAV_INT, i };
    if (hasval) stateMap[key] = sV;
    else stateMap.insert({key, sV});
}

void GameState::setSaveD(std::string key, double d){
    bool hasval = hasValue(key);
    bool toSave = hasval ? stateMap[key].save : false;
    saveVar sV = (saveVar){ toSave, SAV_DOUBLE, d };
    if (hasval) stateMap[key] = sV;
    else stateMap.insert({key, sV});
}
