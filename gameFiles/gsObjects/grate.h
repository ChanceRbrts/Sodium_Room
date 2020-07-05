#ifndef dwr_grate
#define dwr_grate 

#include "../instance.h"

/**
 * A grate! (Water will pass through this, but besides that, it's a solid object...)
 * This will most likely be extended to to include textures and stuff.
 */
class Grate : public Instance{
   private:
      /// Whether or not the texture has been loaded to this instance yet.
      bool loadedTexture;
      /// This makes sure the grate texture is loaded for this grate.
      void loadTexture();
   public:
      /**
       * A constructor for a grate.
       * @param X The left-most coordinate of the grate. (World coords)
       * @param Y The up-most coordinate of the grate. (World coords)
       * @param W The width of the grate. (World coords)
       */
      Grate(double X, double Y, double W);
      /**
       * The drawing code of the grate.
       * Makes sure the grate is drawn based on the grate spritesheet.
       * @param gld The GLUtil's draw functions.
       * @param gls The GLUtil's shader functions.
       */
      void draw(GLDraw* gld, GLShaders* gls);
};

#endif