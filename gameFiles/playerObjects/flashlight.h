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
        /// The textures of the battery.
        int intTexture, extTexture;
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
        /// @return The color of the battery.
        pointDouble getColor();
        /**
         * Remove some charge from the battery.
         * @param deltaTime The amount of time in between the previous frame and this frame.
         */
        void decreaseBattery(double deltaTime);
        /**
         * Recharges the battery. Every battery should charge within 5 seconds.
         */
        void chargeBattery(double deltaTime);
        /**
         * Changes the arc color depending on the battery color.
         */
        void changeArcColor(Arc* a);
        /**
         * Draws the battery as if it's in a HUD.
         */
        void drawHUD(GLDraw* gld, GLShaders* gls, double x, double y);
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
        double upVal;
        /// The velocity of the angle of the flashlight when moving it.
        double angleVel;
        /// The angle of the flashlight
        double angle;
        /// The battery that the flashlight currently has.
        std::vector<Battery*> batts;
        /// The current battery.
        int currentBattery;
        /// The textures of the flashlight for when it's on and off.
        int texOn, texOff;
        /// When to change the opaqueness of the flashlight. (When it's running low on batteries.)
        double animTime, maxAnimTime;
        /// The current opaqueness of the flashlight.
        double curAlpha;
        /// Whether or not the flashlight should be facing right.
        bool facingRight;
        /// The shaderbox for the HUD part of the flashlight.
        ShaderBox* hudBox;
        /// How long the menu is visible for.
        double menuVisible, maxMenuVisible;
        double animCurrBatt, animateSpeed, animateTo, maxMoveTime, moveTime;
        double shakeAnimation, maxShakeAnimation;
        /**
         * Code to move the flashlight up and down.
         * @param deltaTime The amount of time in between the previous frame and this frame.
         * @param keyHeld The array of the keys that are held down.
         */
        void moveFlashlight(double deltaTime, bool* keyHeld);
        void hudAnimation(double deltaTime);
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
         * @param layer The layer that is currently being drawn to.
         */
        void drawEX(GLUtil* glu, int layer);
        /**
         * This will draw things to the HUD related to the flashlight.
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         */
        void drawHUD(GLDraw* gld, GLShaders* gls);
        /**
         * This charges all the batteries that are running low.
         * @param deltaTime The amount of the time in between the previous frame and this frame.
         */
        std::vector<pointDouble> chargeBatteries(double deltaTime);
};

#endif