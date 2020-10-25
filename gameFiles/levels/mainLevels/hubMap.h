#ifndef sdr_hub_map
#define sdr_hub_map

#include "../map.h"
#include "hubFirstFloor.h"
#include "hubBasement.h"

class HubMap : public Map {
    public:
        HubMap(int sID);
};

#endif