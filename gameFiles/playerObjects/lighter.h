#ifndef dwr_player_lighter
#define dwr_player_lighter
#include "../player.h"

/**
 * A player ability that activates a lighter.
 * This lighter makes an arc around the player that restores everything to its default behavior.
 */
class Lighter : public PlayerAbility {
    private:
        /// The current amount of energy the Lighter has.
        double fluid;
        /// The maximum amount of energy the Lighter has.
        double maxFluid;
        /// The amount of energy the lighter has that doesn't decrease the radius.
        double cooldown;
        /// The maximum amount of energy the lighter has that keeps size static.
        double maxCooldown;
        /// This is used for animating the light to make it seem more "flame-like"
        double prevAlpha, newAlpha;
        /// This is used for determining when to change alpha again.
        double animTime, maxAnimTime;
        /// Different factors to change how energy of this ability is being used or being resotred.
        double cooloffFactor, meltFactor, diminishFactor, incFactor;
        /// Whether or not the Lighter is currently on.
        bool on;
        /// Textures for the lighter.
        int texOn, texOff;
        /// Controls how to turn on the Lighter.
        void toggleLight();
        /**
         * Animation for a flickering light.
         * @param deltaTime The time in between the previous frame and this frame.
         */
        void lightFlicker(double deltaTime);
    public:
        /// Constructor for the Lighter
        Lighter();
        /// Deconstructor for the Lighter
        ~Lighter();
        /**
         * Updates the Lighter
         * @param deltaTime The time in between this frame and the previous frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        /**
         * Updates the lighter after collision checks.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void fUpdate(double deltaTime);
        /**
         * This will (eventually, TODO:) draw the lighter. 
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         * @param layer The layer that is currently being drawn to.
         */
        void draw(GLDraw* gld, GLShaders* gls, int layer);
        /**
         * Code to deal with the player colliding with other instances.
         * @param o The instance that collided with the player.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void collided(Instance* o, double deltaTime);
};

#endif