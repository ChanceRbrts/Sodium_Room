#ifndef dwr_player_flashlight
#define dwr_player_flashlight
#include "../player.h"

/**
 * The class representing a battery for a flashlight.
 */
class Battery {
    private:
        /// The color of the arc that this battery allows the flashlight to make.
        double r, g, b;
        /// The amount of charge this battery has in seconds.
        double battery;
        /// The maximum amount of charge this battery has in seconds.
        double maxBattery;
    public:
        /**
         * The Constructor the Battery.
         * @param R The red color of the arc of the battery.
         * @param G The green color of the arc of the battery.
         * @param B The blue color of the arc of the battery.
         * @param mB The amount of charge this battery has in seconds.
         */
        Battery(double R, double G, double B, double mB);
        /// @return The percentage of charge this battery has from 0-1.
        double getBattery();
        /**
         * Remove some charge from the battery.
         * @param deltaTime The amount of time in between the previous frame and this frame.
         */
        void decreaseBattery(double deltaTime);
};

/**
 * An ability that allows you to turn on a flashlight.
 * This flashlight creates an arc that isn't all around the player,
 * but it is a lot larger and can be of different colors depending on batteries.
 */
class Flashlight : public PlayerAbility {
    private:
        /// Whether or not the flashlight is currently on.
        bool on;
        /// The current angle of the flashlight. (From -1 to 1)
        float upVal;
        /// The velocity of the angle of the flashlight when moving it.
        float angleVel;
        /// The battery that the flashlight currently has.
        Battery* batt;
        /// When to change the opaqueness of the flashlight. (When it's running low on batteries.)
        double animTime, maxAnimTime;
        /// The current opaqueness of the flashlight.
        double curAlpha;
        /**
         * Code to move the flashlight up and down.
         * @param deltaTime The amount of time in between the previous frame and this frame.
         * @param keyHeld The array of the keys that are held down.
         */
        void moveFlashlight(double deltaTime, bool* keyHeld);
    public:
        /// The constructor of the flashlight.
        Flashlight();
        /// The deconstructor of the flashlight.
        ~Flashlight();
        /**
         * This updates the flashlight.
         * @param deltaTime The amount of time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down.
         * @param player The player of the game.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        /**
         * Updates the flashlight after collisions happen.
         * @param deltaTime The amount of the time in between the previous frame and this frame.
         */
        void fUpdate(double deltaTime);
        /**
         * This will draw the flashlight (eventually TODO:)
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         */
        void draw(GLDraw* gld, GLShaders* gls);
};

#endif