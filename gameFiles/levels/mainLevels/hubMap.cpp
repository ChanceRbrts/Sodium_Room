#include "hubMap.h"

HubMap::HubMap(int sID) : Map(sID){
    addLevel(new HubFirstFloor(), 0, 0);
    // addLevel(new HubBasement(), 15, 15);
}
