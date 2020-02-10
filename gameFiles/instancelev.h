#ifndef dos_obj_instancelev
#define dos_obj_instancelev

#include "instance.h"
#include "levels/level.h"

/**
 * An instance that comes after the level in compilation.
 * This instance allows manipulation of the levels themselves.
 */
class InstanceLev : public Instance{
    protected:
        bool messWithLevel;
    public:
        InstanceLev(double X, double Y, double W, double H);
        bool canMessWithLevel(){return messWithLevel;};
        virtual void messWithLevels(LevelList* levs, Instance* player);
};

#endif