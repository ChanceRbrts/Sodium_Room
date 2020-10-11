#ifndef sdr_test_map
#define sdr_test_map

#include "../map.h"

/// Include all of the levels that will be included in any maps defined here.
#include "testRain.h"
#include "testFalseBlocks.h"
#include "testHorizontalEnclosed.h"
#include "testJungleObjects.h"
#include "testMultipleLights.h"

#define LEV_TEST_RAIN 0
#define LEV_TEST_FALSEBLOCKS 1
#define LEV_TEST_HORIZONTALENCLOSED 2
#define LEV_TEST_JUNGLEOBJECTS 3
#define LEV_TEST_MULTILIGHTS 4

/**
 * A map used for testing rooms.
 */
class TestMap : public Map {
    private:
        std::vector<Level *> levels;
    public:
        TestMap(int sID);
        ~TestMap();
};

/**
 * A map used specifically for testing 
 * connecting levels together with maps.
 */
class TestMultipleRooms : public Map {
    public:
        TestMultipleRooms(int sID);
};

#endif