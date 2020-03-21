#ifndef dos_obj_instance
#define dos_obj_instance

#include "../glutils/glUtil.h"
#include "../utils/texBook.h"
#include "arc.h"
#include <math.h>

/**
 * The Object Class; these are the instances that we are updating!
 * (Called Instance here because I'm used to not saying Object for these)
 */
class Instance{
   protected:
      // The list of textures for the class. Probably will be used for animations?
      //std::vector<int> textures;
      // Whether or not we have a texture to use.
      bool hasTexture;
      // The current textureID that we want to use.
      int textureID;
      // Terminal Velocity
      double termY;
      /*
       * The color of the instance when drawn as a rectangle.
       * (If you want to use a texture, make sure r, g, and b are all 1.)
       */
      double r, g, b;
      bool gravity, onGround, immovable, solid;
      // Should always be false except for the player.
      bool playerRef;
      bool remove;
      bool hidden;
      // The boolean to say whether or not you need the GLUtil class and not just GLDraw and GLShaders for drawing.
      bool needExtra;
      // Some objects need to do solid collisions with only some objects.
      // If solid is true, this is a blacklist; if solid is false, this is a whitelist for solid object collisions.
      std::vector<std::string> colList;
      std::vector<ArcInfo> arcList;
      // Useful for identifying different objects
      std::string name;
      // Simple gravity calculations.
      void doGravity(double deltaTime);
   public:
      // Instances that were created by this one. (That work globally.)
      std::vector<Instance *> toAdd;
      double x, y;
      // Velocity (Pixels per seconds)
      double dX, dY;
      double w, h;
      int texID(){return textureID;};
      virtual bool canMessWithLevel(){return false;};
      // See if the object needs to be deleted.
      double getR(){return r;};
      double getG(){return g;};
      double getB(){return b;};
      void hide(bool h);
      void changeTexture(int tex, bool untint);
      bool canRemove(){return remove;};
      bool isPlayer(){return playerRef;};
      // Check the whitelist/blacklist with the other index. 
      bool isSolid(std::string other);
      std::string getName(){return name;};
      /**
       * Constructor for the instance.
       * (X, Y, W, and H are in unit coordinates (Multiplied by 32 pixels))
       * @param X The left-most position of the instance.
       * @param Y The up-most position of the instance.
       * @param W The width of the instance.
       * @param H The height of the instance.
       */
      Instance(double X, double Y, double W, double H);
      virtual ~Instance(){};
      /**
       * Updates the object. This is the function that you want to call.
       * Does some things like possible gravity and then calls update.
       * @param deltaTime The time in between this frame and the previous frame.
       * @param keyPressed The array of the keys pressed this frame.
       * @param keyHeld The array of the keys that are held down.
       * @param player The player instance.
       */
      void upd(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
      /**
       * Updates the object. This is the function that you want to overwrite.
       * @param deltaTime The time in between this frame and the previous frame.
       * @param keyPressed The array of keys pressed this frame.
       * @param keyHeld The array of the keys that are held down.
       */
      virtual void update(double deltaTime, bool* keyPressed, bool* keyHeld){};
      /**
       * Updates the object. This is the function that you want to overwrite. 
       * (Only overwrite this if this instance's behavior is affected by the behavior.)
       * @param deltaTime The time in between this frame and the previous frame.
       * @param keyPressed The array of keys pressed this frame.
       * @param keyHeld The array of the keys that are held down.
       * @param player The player instance.
       */
      virtual void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player){
         update(deltaTime, keyPressed, keyHeld);
      };
      /**
       * This actually updates the position of the object after collisions happen.
       * @param deltaTime The time in between this frame and the previous frame.
       */
      void finishUpdate(double deltaTime);
      /**
       * Extra things that happen along with finishUpdate.
       * This is the function that you may want to override.
       * @param deltaTime The time in between this frame and the previous frame.
       */
      virtual void fUpdate(double deltaTime){};
      /**
       * Checks and handles collisions between another object.
       * @param o The instance that's being checked for collision
       * @param deltaTime The time in between this frame and the previous frame.
       * @param cornerCheck Whether we check the corners for solid objects or just the edges.
       */
      void collision(Instance* o, double deltaTime, bool cornerCheck);
      /**
       * Checks and handles collisions with arcs.
       * @param o The instance that defines the arc.
       * @param deltaTime The time inbetween this frame and the previous frame.
       */
      bool arcCollision(Arc* o, double deltaTime);
      /**
       * Deals with the collision with arcs.
       * @param o The arc that was collided with.
       */
      void arcCol(Arc* o, double deltaTime, int id);
      /**
       * If a collision happens, this function gets called.
       * This is code you want to get called if something collides with the object.
       * @param o The instance that has been collided with
       * @param deltaTime The time in between this frame and the previous frame.
       */
      virtual void collided(Instance* o, double deltaTime){};
      /**
       * The code to draw the instance. (This you want to implement.)
       * I force GLDraw and GLShaders here to recommend people only do drawing code.
       * @param gld The GLUtil's draw functions.
       * @param gls The GLUtil's shader functions.
       */
      virtual void draw(GLDraw* gld, GLShaders* gls);
      /**
       * The code to draw the instance. (This you want to implement.)
       * I recommend you use GLDraw.
       * This is ONLY if you need to use GLUtil for something other than drawing or shading.
       * @param glu The GLUtil to use for drawing.
       */
      virtual void drawEX(GLUtil* glu);
      /**
       * The code to draw the instance.
       * @param glu The GLUtil to use for drawing.
       */
      void draw(GLUtil* glu);
};

/**
 * A double linked list for Instances.
 */
struct Instances{
   Instance* i;
   Instances* prev;
   Instances* next;
};

#endif