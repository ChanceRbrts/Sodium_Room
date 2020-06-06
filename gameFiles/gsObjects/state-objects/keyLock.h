#ifndef dwr_state_keylock
#define dwr_state_keylock
#include "../../instance.h"

/**
 * An object representing some sort of key.
 * Picking up this object changes the state of the game.
 */
class Key : public Instance{
    private:
        /// The name of the variable to interact with on the game state.
        std::string lName;
    public:
        /**
         * Constructor for the Key
         * @param X The left-most position of the key (In world coords)
         * @param Y The up-most position of the key (In world coords)
         * @param lock The variable to interact with on the game state.
         */
        Key(double X, double Y, std::string lock);
        /**
         * Constructor for the Key
         * @param X The left-most position of the key (In world coords)
         * @param Y The up-most position of the key (In world coords)
         * @param lock The variable to interact with on the game state.
         * @param perm Whether or not this variable is saveable (Default is true)
         */
        Key(double X, double Y, std::string lock, bool perm);
        /**
         * Deal with collisions of other objects
         * @param o The object that has been collided with.
         * @param deltaTime The time in between the previous frame and this frame.
         */
        void collided(Instance* o, double deltaTime);
};

/**
 * TODO: Figure out what to do with this.
 */
class Lock : public Instance{

};

#endif