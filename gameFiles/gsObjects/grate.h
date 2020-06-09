#ifndef dwr_grate
#define dwr_grate 

#include "../instance.h"

/**
 * A grate! (Water will pass through this, but besides that, it's a solid object...)
 * This will most likely be extended to to include textures and stuff.
 */
class Grate : public Instance{
   public:
      /**
       * A constructor for a grate.
       * @param X The left-most coordinate of the grate. (World coords)
       * @param Y The up-most coordinate of the grate. (World coords)
       * @param W The width of the grate. (World coords)
       */
      Grate(double X, double Y, double W);
};

#endif