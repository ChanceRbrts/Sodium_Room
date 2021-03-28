#ifndef dwr_state_button
#define dwr_state_button
#include "../../instance.h"

/**
 * A simple button that an instance can press.
 * Comes in two types: Press once or press multiple times!
 * These buttons directly interact with the game state.
 */
class Button : public Instance {
    protected:
        /// How many times the button has been pressed.
        int pressed;
        /// The max amount of times a button can be pressed before moving back to the default state.
        int maxPress;
        /// Whether the button can be pressed multiple times.
        bool multiPress;
        /// Whether the button is currently being pressed down.
        bool pressDown;
        /// Whether to connect with the state when determining the button press.
        bool updateState;
        /// Which direction to press the button. (0->down, 1->right, 2->up, 3->left)
        int pressDir;
        /// The threshold for how long an instance can be off a button before it's considered as not pressing it.
        double pEpsilon;
        /// The variable in the game state to interact with.
        std::string pressedVal;
        /// The instances that are colldied with the button, and how long they have not been colliding with the button.
        std::map<Instance*, double> collWith;
        /// Whether the button has been pressed last frame.
        bool prevPress;
        /// A function to change the state of the pressed button.
        virtual void changeState();
        /**
         * A helper function for the constructor to set up the orientation of the button.
         * @param dir The direction the button is facing. (0->down, 1->right, 2->up, 3->left)
         */
        void setUp(int dir);
        /**
         * A function to update which instances are still colliding with the button.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void unpushCheck(double deltaTime);
        /**
         * Toggle a button push.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void changePress(double deltaTime);
        void stateChange();
    public:
        /**
         * Constructor for a button push
         * @param X The left-most coordinate of the button (In world coords)
         * @param Y The up-most coordinate of the button (In world coords)
         * @param direction The direction that the button needs to be pressed. (0->down, 1->right, 2->up, 3->left)
         * @param pressedValue The variable that the button interacts with in the game state.
         * @param updateMe Whether or not to update the button's state when the variable itself changes. 
         */
        Button(double X, double Y, int direction, std::string pressedValue, bool updateMe = true);
        /**
         * Constructor for a button push
         * @param X The left-most coordinate of the button (In world coords)
         * @param Y The up-most coordinate of the button (In world coords)
         * @param direction The direction that the button needs to be pressed. (0->down, 1->right, 2->up, 3->left)
         * @param pressedValue The variable that the button interacts with in the game state.
         * @param maxPressed The amount of states a button has. (<= 0 means this can't be pressed multiple times)
         * @param updateMe Whether or not to update the button's state when the variable itself changes. 
         */
        Button(double X, double Y, int direction, std::string pressedValue, int maxPressed, bool updateMe = true);
        /**
         * Updates the button.
         * @param deltaTime The time in between this frame and the previous frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        // void draw(GLDraw* gld, GLShaders* gls, int layer);
        /**
         * Deals with collisions of the object.
         * @param o The other object that's colliding with the button.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void collided(Instance* o, double deltaTime);
        /// Make the variable in the game state saveable.
        void makePermanent();
};

#endif