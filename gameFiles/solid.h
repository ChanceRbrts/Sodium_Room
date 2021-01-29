#ifndef dos_obj_solid
#define dos_obj_solid 

#include "instance.h"

/**
 * A solid object.
 * This will most likely be extended to to include textures and stuff.
 */
class Solid : public Instance{
    public:
        /**
         * The constructor for a solid object.
         * @param X The left-most position of the instance. (Unit coords)
         * @param Y The up-most position of the instance. (Unit coords)
         */
        Solid(double X, double Y);
};

class SemiSolid : public Instance{
    public:
        /**
         * The constructor for a semi-solid object.
         * @param X The left-most position of the instance. (Unit coords)
         * @param Y The up-most position of the instance. (Unit coords)
         */
        SemiSolid(double X, double Y);
};

#endif