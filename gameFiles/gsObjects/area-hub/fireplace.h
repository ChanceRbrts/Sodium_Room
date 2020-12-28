#ifndef dwr_hub_fireplace
#define dwr_hub_fireplace

#include "../../instance.h"

/**
 * The fireplace in the middle of the Hub.
 */
class Fireplace : public Instance {
    private:
        /// Whether or not the fireplace has been lit.
        bool lit;
        /// The variable name that the fireplace being lit is attached to
        std::string lName;
    public:
        /**
         * The constructor for the fireplace.
         * @param X The x position in world coords for the fireplace.
         * @param Y The y posiiton in world coords for the fireplace.
         * @param litName The variable name that's connected to whether the fireplace is lit or not.
         */
        Fireplace(double X, double Y, std::string litName);
        /**
         * Initializes the drawing layers of the fireplace.
         */
        std::vector<int> initLayers();
        /**
         * Updates the fireplace.
         * Checks if the lighter is on the fireplace and lights the fireplace if that's the case.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
};

#endif