#ifndef sdr_jung_map
#define sdr_jung_map

#include "../map.h"
#include "rainHallway.h"
#include "flashlight_area.h"
#include "flashlight_exit.h"

#define LEV_JUNG_RAINHALLWAY 0
#define LEV_JUNG_FLASHLIGHTEXIT 1
#define LEV_JUNG_FLASHLIGHTAREA 2

/**
 * The map that contains levels corresponding to the jungle/garden area.
 */
class JungleMap : public Map {
    public:
        JungleMap(int sID);
};

#endif