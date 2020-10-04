#ifndef sdr_jung_map
#define sdr_jung_map

#include "../map.h"
#include "rainHallway.h"

#define LEV_JUNG_RAINHALLWAY 0

/**
 * The map that contains levels corresponding to the jungle/garden area.
 */
class JungleMap : public Map {
    public:
        JungleMap(int sID);
};

#endif