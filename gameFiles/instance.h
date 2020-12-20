#ifndef dos_obj_instance
#define dos_obj_instance

#include "../glutils/glUtil.h"
#include "../utils/texBook.h"
#include "../utils/gameState.h"
#include "arc.h"
#include <math.h>

#define LAYER_NORMAL 0
#define LAYER_BACK -2147483648
#define LAYER_FRONT 2147483647

/**
 * The Object Class; these are the instances that we are updating!
 * (Called Instance here because I'm used to not saying Object for these)
 */
class Instance{
   protected:
      // The list of textures for the class. Probably will be used for animations?
      //std::vector<int> textures;
      /// Whether or not we have a texture to use.
      bool hasTexture;
      /// The current textureID that we want to use.
      int textureID;
      /// Terminal Velocity
      double termY;
      /**
       * The color of the instance when drawn as a rectangle.
       * (If you want to use a texture, make sure r, g, and b are all 1.)
       */
      double r, g, b;
      /// Multipliers for dX and dY
      double dXModifier, dYModifier;
      /// Used for slowly changing the dX multiplier
      double startDXM, targetDXM;
      /// Used for slowly changing the dY multiplier
      double startDYM, targetDYM;
      /// The amount of time to change the dX or dY multiplier
      double dXChangeTime, dYChangeTime;
      /// Whether the instance is affected by gravity.
      bool gravity;
      /// Whether the instance is standing on ground.
      bool onGround;
      /// Whether or not the instance can be moved via collisions.
      bool immovable;
      /// Whether or not the instance typically uses solid collisions.
      bool solid;
      /// Should always be false except for the player.
      bool playerRef;
      /// Whether or not the instance wants to be deleted/removed from the linked list.
      bool remove;
      /**
       * Whether or not to delete the instance after removing it from the linked list.
       * ONLY MAKE THIS FALSE IF THIS INSTANCE IS CONNECTED AND DELETED WITH ANOTHER INSTANCE.
       */
      bool deleteIfRemoved;
      /// Whether or not the instance is visible to the screen.
      bool hidden;
      /// Whether or not the instance has the same hitbox as a wall.
      bool stuckToWall;
      /// The dX and dY that the player had before collision checks.
      double collDX, collDY;
      /// The boolean to say whether or not you need the GLUtil class and not just GLDraw and GLShaders for drawing.
      bool needExtra;
      /// Whether or not we initialized drawing layers.
      bool initedLayers;
      /**
       * Some objects need to do solid collisions with only some objects.
       * If solid is true, this is a blacklist; if solid is false, this is a whitelist for solid object collisions.
       */
      std::vector<std::string> colList;
      /// A list of arcs that the instance collided with.
      std::vector<ArcInfo> arcList;
      /// Useful for identifying different objects.
      std::string name;
      /// The drawing layers that the instance draws to.
      std::vector<int> layers; 
      /**
       * Initializes the layers vector to determine what layers to draw to.
       * @return The layers to draw to.
       */
      virtual std::vector<int> initLayers();
      /**
       * Simple gravity calculations
       * @param deltaTime The time in between this frame and the previous frame.
       */
      void doGravity(double deltaTime);
   public:
      /// Instances that were created by this one. (To be added to the game logic.)
      std::vector<Instance *> toAdd;
      /// The position of the instance.
      double x, y;
      /// Velocity (Pixels per seconds)
      double dX, dY;
      /// The previous velocity (Pixels per seconds)
      double prevDX, prevDY;
      /// The size of the instance.
      double w, h;
      /// @return The ID of the texture to use.
      int texID(){return textureID;};
      /// @return Whether or not the instance can mess with the level.
      virtual bool canMessWithLevel(){return false;};
      /// @return The red tint of the instance.
      double getR(){return r;};
      /// @return The green tint of the instance.
      double getG(){return g;};
      /// @return The blue tint of the instance.
      double getB(){return b;};
      /// @return The x velocity before collision checks.
      double getCollDX(){return collDX;};
      /// @return The y velocity before collision checks.
      double getCollDY(){return collDY;};
      /// Make the instance think it's on the ground.
      void ground(){onGround = true;};
      /// @return A list of arc representations that the instance is currently colliding with.
      std::vector<ArcInfo> getArcList(){return arcList;};
      /**
       * Decide whether or not the instance is visible.
       * @param h Is the instance invisible?
       */
      void hide(bool h);
      /**
       * Linearly change the multiplier for velocity.
       * @param horizontal Whether or not the multiplier change is for dX and not dY
       * @param to What to change the velocity multiplier to.
       * @param timeMod The amount of time to take to change the multiplier to.
       * @param changeSpeed Whether or not to adjust the velocity to the new multiplier (Makes timeMod 0)
       */
      void changeDVModifier(bool horizontal, double to, double timeMod, bool changeSpeed);
      /**
       * Change the current texture
       * @param tex The texture ID to change the texture into.
       * @param untint Whether or not to remove the tint of the instance.
       */
      void changeTexture(int tex, bool untint);
      /// @return Whether or not the instance wants to be deleted/removed from the level.
      bool canRemove(){return remove;};
      /// @return Whether or not to delete the instance if it's removed from the level.
      bool canDeleteIfRemoved(){return deleteIfRemoved;};
      /// @return Whether or not an object is immovable.
      bool isImmovable(){return immovable;};
      /// @return Whether or not the instance is a player.
      bool isPlayer(){return playerRef;};
      // Check the whitelist/blacklist with the other index. 
      /**
       * Check whether or not the instance is solid in relation to another instance.
       * @param other The name of the other instance to check with.
       * @return Whether or not the instance is solid.
       */
      bool isSolid(std::string other);
      /// @return The name of the instance.
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
      /// The Deconstructor for the instance.
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
       * @param layer The layer that is currently being drawn to.
       */
      virtual void draw(GLDraw* gld, GLShaders* gls, int layer);
      /**
       * The code to draw the instance. (This you want to implement.)
       * I recommend you use GLDraw.
       * This is ONLY if you need to use GLUtil for something other than drawing or shading.
       * @param glu The GLUtil to use for drawing.
       * @param layer The layer that is currently being drawn to.
       */
      virtual void drawEX(GLUtil* glu, int layer);
      /**
       * The code to draw the instance.
       * @param glu The GLUtil to use for drawing.
       * @param layer The layer that is currently being drawn to.
       */
      void draw(GLUtil* glu, int layer);
      /**
       * Get the layers that this instance needs to be drawn to.
       * A layer in this case represents the drawing order, where a smaller layer means it's drawn first.
       * @return The list of layers to draw to.
       */
      std::vector<int> getLayers();
};

/// A doubly linked list for Instances, but used in the case of drawing order.
struct DrawnInstance{
   /// The layer to draw to. This determines the order in which instances get drawn.
   int layer;
   /// The instance to draw.
   Instance* i;
   /// The instance that's before this in the drawing order in this layer.
   DrawnInstance* prev;
   /// The instance that's after this in the drawing order in this layer.
   DrawnInstance* next;
};

/**
 * A doubly linked list for Instances.
 */
struct Instances{
   /// @param i The current instance.
   Instance* i;
   /// @param prev The instance before this one on the linked list.
   Instances* prev;
   /// @param next The instance after this one on the linked list.
   Instances* next;
   /// @param draw The instances that represents where it's being drawn.
   std::vector<DrawnInstance*> drawn;
};

#endif