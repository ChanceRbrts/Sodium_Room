#ifndef dwr_enclosedlevel
#define dwr_enclosedlevel

#include "../instancelev.h"
#include <math.h>

/**
 * An instance that has a collapsible level in it.
 */
class EnclosedLevel : public InstanceLev {
    private:
        /// A check to see if this needs to create shaders
        bool shaderCheck;
        /// Whether or not this is connected to an arc.
        bool connected;
        /// Whether or not the level opens up horizontally or vertically.
        bool openHorizontally;
        /// Whether or not the instance needs to push part of the other levels.
        bool pushLevel;
        /// Whether or not the level is part of the scene.
        bool prevLevelUp, levelUp;
        /// The time that the level's currently opening.
        float openTime;
        /// The time it takes for the level to open.
        float maxOpenTime;
        /// The true width/height of the level.
        double trueW;
        /// The current width/height of the level.
        double lastW;
        /// Animation time for the dotted line and the diamonds.
        double time;
        /// The level that is collapsed into this instance.
        Level* lev;
        /**
         * A check to make sure we actually have created shaders for this.
         * @param gls The GLUtil's shader functions.
         */
        void checkShaders(GLShaders* gls);
        /// This checks the arc list to update whether or not the level is opened or closed.
        void checkOpen();
    protected:
        /**
         * Initializes the drawing layers.
         * This is special since we need to draw rain on 2 different layers.
         * @return The layers to draw to.
         */
        std::vector<int> initLayers();
    public:
        /// A boolean to determine if the level should expand or collapse
        bool open;
        /**
         * Constructor for Enclosed Level
         * @param X The left-most coordinate of the level (In world coords)
         * @param y The up-most coordinate of the level (In world coords)
         * @param W The width of the level (In world coords, 0 if it opens horizontally)
         * @param H The height of the level (In world coords, 0 if it opens vertically)
         * @param l The level to expand and collapse.
         */
        EnclosedLevel(double X, double Y, double W, double H, Level* l);
        /**
         * Draws the collapsible level.
         * @param glu The GLUtil to use.
         * @param layer The layer that is currently being drawn to.
         */
        void drawEX(GLUtil* glu, int layer);
        /**
         * Updates the collapsible level
         * @param deltaTime The time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down. 
         * @param player The player of the game.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        /**
         * The code that will expand/collapse the level by bisecting parts of the level.
         * @param levs The list of levels loaded in the game.
         * @param player The player of the game.
         */
        void messWithLevels(LevelList* levs, Instance* player);
        /// This disconnects the enclosed level from an arc.
        void disconnect();
};

#endif