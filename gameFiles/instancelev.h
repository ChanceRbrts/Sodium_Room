#ifndef dos_obj_instancelev
#define dos_obj_instancelev

#include "instance.h"
#include "levels/level.h"
#include "levels/map.h"

/**
 * An instance that comes after the level in compilation.
 * This instance allows manipulation of the levels themselves.
 */
class InstanceLev : public Instance{
    protected:
        /// Whether or not the instance can mess with levels.
        bool messWithLevel;
    public:
        /**
         * Constructor for the instance.
         * (X, Y, W, and H are in unit coordinates (Multiplied by 32 pixels))
         * @param X The left-most position of the instance.
         * @param Y The up-most position of the instance.
         * @param W The width of the instance.
         * @param H The height of the instance.
         */
        InstanceLev(double X, double Y, double W, double H);
        /// @return Whether or not the instance can mess with levels.
        bool canMessWithLevel(){return messWithLevel;};
        /**
         * Code that determines how levels are messed with.
         * @param levs The list of levels loaded in the game.
         * @param player The player of the game.
         */
        virtual void messWithLevels(LevelList* levs, Instance* player);
        virtual void messWithMaps(std::vector<Map *> maps);
};

#endif