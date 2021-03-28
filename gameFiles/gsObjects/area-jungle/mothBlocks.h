#ifndef obj_jung_mothblocks
#define obj_jung_mothblocks

#include "../fakeSolid.h"

/**
 * A fake solid that is being controlled by MothBlocks
 * This has functions to control the MothBlock
 */
class MothBlock : public FakeSolid {
    protected:
        /// The position of the blocks relative to the center of the moth blocks.
        double startX, startY;
    public:
        /**
         * The constructor of the moth blocks.
         * @param X The x position in unit coords compared to the center of the MothBlocks.
         * @param Y The y position in unit coords compared to the center of the MothBlocks.
         * @param cX The x position in unit coords of the center of the MothBlocks.
         * @param cY The y position in unit coords of the center of the MothBlocks.
         */
        MothBlock(double X, double Y, double cX, double cY);
        /// Detaches this block from the moth blocks. Used only when about to be deleted.
        void detach();
        /**
         * Updates the position of the MothBlock depending on certain things.
         * @param move How much the moth block is moving from 0-1; 1 is completely stationary.
         * @param cX The x position in unit coords of the center of the MothBlocks.
         * @param cY The y position in unit coords of the center of the MothBlocks.
         * @param reset Whether or not the moth blocks are being reset.
         */
        void updateBlock(double move, double cX, double cY, bool reset);
};

class MothBlocks : public InstanceLev {
    private:
        /// The list of Fake Solids that the MothBlocks controls
        std::vector<MothBlock *> fakeSolids;
        /// The variable name to reset the blocks to.
        std::string resetVar;
        /// Determines whether to check if the blocks have reset.
        bool canReset;
        /// Determines whether or not the blocks are currently resetting.
        bool resetting;
        /// Whether or not the Fake Solids have been placed down in a level.
        bool blocksPlacedDown;
        /// Whether or not the Fake Solids CAN be placed down in a level.
        bool canPlaceBlocks;
        /// Internal timers to determine movement of the blocks; move=maxMove means no movement for a while.
        double move, maxMove;
        /// The starting position of the moth blocks.
        double startX, startY;
        /// Used for positioning purposes
        bool loadedIn;
        /**
         * The update code when resetting an arc.
         * @param deltaTime The time in seconds since the previous frame.
         */
        void reset(double deltaTime);
        /**
         * The normal behavior of an arc, where the blocks move towards lights.
         * @param deltaTime The time in seconds since the previous frame.
         */
        void moveToArc(double deltaTime);
    public:
        /**
         * Constructor of the Moth Blocks
         * @param X The x position of the left-hand side of the blocks in unit-coords.
         * @param Y The y position of the up-most side of the blocks in unit-coords.
         * @param filename The file name of the level data of the moth blocks.
         * @param resetName The variable name that determines whether the moth blocks are reset.
         */
        MothBlocks(double X, double Y, std::string filename, std::string resetName = "");
        /// Deconstructor of the moth blocks
        ~MothBlocks();
        /**
         * Updates the MothBlocks
         * @param deltaTime The time in seconds since the previous frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down. 
         * @param player The player of the game.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        /**
         * This draws all of the Fake Solids if the Fake Solids are not a part of the level.
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         * @param layer The layer that is currently being drawn to.
         */
        void draw(GLDraw* gld, GLShaders* gls, int layer);
        /**
         * If there's no light connecting to the MothBlocks, 
         * it tries to go to the nearest light in the sub-level.
         * @param levs The list of levels loaded in the game.
         * @param lv The level that the instance belongs to.
         * @param map The map that the instance belongs to.
         * @param player The player of the game.
         * @return Whether or not layers need to be reloaded. 
         */
        bool messWithLevels(LevelList* levs, Level* lv, Map* map, Instance* player);
        /**
         * Checks if the player has collided with the fake blocks.
         * If the player has, the blocks cannot be added to the level yet.
         * @param o The instance that's being checked for collision
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void collided(Instance* o, double deltaTime);
};

#endif