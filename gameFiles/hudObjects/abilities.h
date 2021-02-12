#ifndef sdr_hud_abilities
#define sdr_hud_abilities

#include "../instance.h"
#include "../player.h"

class HUDAbilities : public Instance {
    private:
        Instances* head;
        Instances* tail;
        Instances* selected;
    public:
        HUDAbilities();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void draw(GLDraw* gld, GLShaders* gls, int layer);
        void addAbility(PlayerAbility* ability);
};

#endif