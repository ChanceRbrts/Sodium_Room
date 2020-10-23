#include "hubMap.h"

HubMap::HubMap(int sID) : Map(sID){
    addLevel(new HubFirstFloor(), 0, 0);
}
