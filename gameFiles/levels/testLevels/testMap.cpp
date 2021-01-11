#include "testMap.h"

TestMap::TestMap(int sID) : Map(sID){
    levels.push_back(new TestRain());
    levels.push_back(new TestFalseBlocks());
    levels.push_back(new TestHorizontalEnclosed(1));
    levels.push_back(new TestJungleObjects());
    levels.push_back(new TestMultipleLights());
    levels.push_back(new TestHorizontalEnclosed(2));
    addLevel(levels[LEV_TEST_HORIZONTALENCLOSED2], 0, 0);
}

TestMap::~TestMap(){
    for (int i = 0; i < levels.size(); i++){
        delete levels[i];
    }
    levels.clear();
}

TestMultipleRooms::TestMultipleRooms(int sID) : Map(sID){
    int length = 3;
    addLevel(new BasicLevel("testmapLevels/testmapLeft", 10, 13), -length*20, 0);
    for (int i = -length+1; i < length; i++){
        addLevel(new BasicLevel("testmapLevels/testmapMiddle", 10, 13), i*20, 0);
    }
    addLevel(new BasicLevel("testmapLevels/testmapRight", 10, 13), length*20, 0);
}
