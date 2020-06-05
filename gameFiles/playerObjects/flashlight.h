#ifndef dwr_player_flashlight
#define dwr_player_flashlight
#include "../player.h"

class Flashlight : public PlayerAbility {
    private:
        bool on;
        float upVal, angleVel;
        float battery, maxBattery;
        void moveFlashlight(double deltaTime, bool* keyHeld);
    public:
        Flashlight();
        ~Flashlight();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void fUpdate(double deltaTime);
        void draw(GLDraw* gld, GLShaders* gls);
};

#endif