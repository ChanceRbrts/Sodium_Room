#ifndef dwr_jungle_platform
#define dwr_jungle_platform

#include "../../instance.h"
#include "../../player.h"

/**
 * A platform of honey that changes colors and properties when different lights are flashed on them.
 * Red -> Horizontal Stickiness
 * Green -> Lack of Jumping (0.5 = Normal Jumping)
 * Blue -> Vertical Stickiness
 */
class HoneyPlatform : public Instance {
    private:
        /// The amount of time it takes for the color of the object to go from 0 to 1
        double colorSwapTime;
        /// The starting color of the honey from 0 to 1
        double startColR, startColG, startColB;
        /**
         * Slowly move a color over to another value.
         * @param vMove The color to move to.
         * @param vTo The number to move the color to.
         * @param deltaTime The time in between the previous frame and this frame.
         */
        double moveValueTo(double* vMove, double vTo, double deltaTime);
        /// A list of instances that have been collided with, and whether or not they've been collided with this frame.
        std::map<Instance *, bool> collidedInstances;
        /// Whether or not the platform changed color that frame.
        bool changedColor;
    public:
        /**
         * Constructor for the honey platform.
         * @param X The left-most position of the honey platform. (In world coords)
         * @param Y The up-most position of the honey platform. (In world coords)
         * @param W The width/height of the honey platform. (In world coords) (The other is 1 world coord.)
         * @param horizontal Whether or not W affects the width or height of the platform.
         */
        HoneyPlatform(double X, double Y, double W, bool horizontal);
        /**
         * Constructor for the honey platform.
         * @param X The left-most position of the honey platform. (In world coords)
         * @param Y The up-most position of the honey platform. (In world coords)
         * @param W The width/height of the honey platform. (In world coords) (The other is 1 world coord.)
         * @param R The default red color of the honey from 0 to 1.
         * @param G The default green color of the honey from 0 to 1.
         * @param B The default blue color of the honey from 0 to 1.
         * @param horizontal Whether or not W affects the width or height of the platform.
         */
        HoneyPlatform(double X, double Y, double W, double R, double G, double B, bool horizontal);
        // void draw(GLDraw* gld, GLShaders* gls, int layer);
        /**
         * The update function for the honey platform.
         * @param deltaTime The time in between this frame and the previous frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down. 
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        /**
         * Deals with objects colliding with the platform.
         * @param o The object that collided with the platform.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void collided(Instance* o, double deltaTime);
};

#endif