#ifndef sdr_level_rainhallway
#define sdr_level_rainhallway
#include "../level.h"

/**
 * This is a hallway with three red arcs that alter the rain.
 * This makes the player either use the lighter to go past or have good timing.
 * The ending has red rain that forces the player downwards.
 * (Unless their lighter is completely full?)
 */
class RainHallwayLevel : public Level{
    protected:
        Arc* a1;
        Arc* a2;
        Arc* a3;
        double anim, maxAnim;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
    public:
        RainHallwayLevel();
        std::vector<Arc *> createArcs();
        void updateLevel(double deltaTime, Instance* player);
};

#endif