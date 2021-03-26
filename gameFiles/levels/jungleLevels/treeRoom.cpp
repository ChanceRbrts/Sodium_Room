#include "treeRoom.h"

TreeRoom::TreeRoom() : Level(){
    filePath = "jungleLevels/tree_room";
}

std::vector<Instance *> TreeRoom::makeLevel(std::vector<Instance*> previous){
    previous.push_back(new FakeSolids(0, 12, "jungleLevels/tree_room_interior", true));
    return previous;
}

std::vector<CameraObject *> TreeRoom::createCameraObjects(){
    std::vector<CameraObject *> cams;
    cams.push_back(new OneWayCameraObject(0, 2, h/32-4, 3));
    return cams;
}