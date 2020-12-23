#ifndef obj_jung_mothblocks
#define obj_jung_mothblocks

#include "../fakeSolid.h"

class MothBlock : public FakeSolid {
    protected:
        double startX, startY;
    public:
        MothBlock(double X, double Y, double cX, double cY);
        void detach();
        void updateBlock(double move, double cX, double cY);
};

class MothBlocks : public InstanceLev {
    private:
        std::vector<MothBlock *> fakeSolids;
        bool blocksPlacedDown;
        bool canPlaceBlocks;
        double move, maxMove;
        // Implementation through FakeSolids moving around? Maybe...
    public:
        MothBlocks(double X, double Y, std::string filename);
        ~MothBlocks();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void draw(GLDraw* gld, GLShaders* gls, int layer);
        bool messWithLevels(LevelList* levs, Level* lv, Map* map, Instance* player);
        void collided(Instance* o, double deltaTime);
};

#endif