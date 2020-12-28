#ifndef dwr_obj_lightbox
#define dwr_obj_lightbox

#include "../instance.h"

/**
 * A box that the player can "light up" with a lighter.
 * This light box will then have an arc that acts as a white light.
 */
class LightBox : public Instance {
    private:
        /// Whether or not the lighter has been lit.
        bool lit;
        /// Internal timers for transitions between being lit.
        float time, maxTime;
        /// The arc that corresponds to a lit lightbox.
        Arc* a;
    public:
        /**
         * Constructor for a light box
         * @param X The left-most position of the box in unit coords.
         * @param Y The up-most position of the box in unit coords.
         */ 
        LightBox(double X, double Y);
        /// Initializes the drawing layers in which the LightBox will be used.
        std::vector<int> initLayers();
        /**
         * Handles the LightBox being lit and unlit, and the transitions in between those two.
         * @param deltaTime The time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        /// @return The arc that corresponds to the lightbox being lit.
        Arc* getArc();
};

#endif