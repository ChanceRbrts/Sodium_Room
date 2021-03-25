#ifndef sdr_jung_map
#define sdr_jung_map

#include "../map.h"
#include "rainHallway.h"
#include "flashlight_area.h"
#include "flashlight_exit.h"
#include "mothEscort.h"
#include "mothEscortHoney.h"
#include "growFruit.h"

#define LEV_JUNG_RAINHALLWAY 0
#define LEV_JUNG_FLASHLIGHTEXIT 1
#define LEV_JUNG_FLASHLIGHTAREA 2
#define LEV_JUNG_FLASHLIGHTUPPER 3
#define LEV_JUNG_FLASHLIGHTLOWER 4
#define LEV_JUNG_MOTHESCORT 5
#define LEV_JUNG_GROWFRUIT 6
#define LEV_JUNG_MOTHPLUSHONEY 7
#define LEV_JUNG_UNDERPASS 8
#define LEV_JUNG_MOTHESCORT2 9
#define LEV_JUNG_BROKENASCEND 10
#define LEV_JUNG_TREEROOM 11

/**
 * The map that contains levels corresponding to the jungle/garden area.
 */
class JungleMap : public Map {
    public:
        JungleMap(int sID);
};

#endif