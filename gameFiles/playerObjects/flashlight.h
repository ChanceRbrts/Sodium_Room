#ifndef dwr_player_flashlight
#define dwr_player_flashlight
#include "../player.h"

class Battery {
    private:
        double r, g, b;
        double battery, maxBattery;
    public:
        Battery(double R, double G, double B, double mB);
        double getBattery();
        void decreaseBattery(double deltaTime);
};

class Flashlight : public PlayerAbility {
    private:
        bool on;
        float upVal, angleVel;
        Battery* batt;
        double animTime, maxAnimTime, curAlpha;
        void moveFlashlight(double deltaTime, bool* keyHeld);
    public:
        Flashlight();
        ~Flashlight();
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        void fUpdate(double deltaTime);
        void draw(GLDraw* gld, GLShaders* gls);
};

#endif