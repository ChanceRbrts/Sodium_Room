#ifndef dos_obj_solid
#define dos_obj_solid 

#include "instance.h"

/**
 * A solid object.
 * This will most likely be extended to to include textures and stuff.
 */
class Solid : public Instance{
    public:
        Solid(double X, double Y);
};

#endif