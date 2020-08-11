#ifndef dwr_jungle_firefly
#define dwr_jungle_firefly

#include "../../instance.h"

/**
 * An instance that wraps around an arc.
 */
class PointLight : public Instance{
    protected:
        /// The light that is connected to the point light.
        Arc* light;
        /// Determines the radius of the point light (wide*maxRadius)
        double wide, maxRadius;
        /**
         * Updates the arc to be the position of the pointlight.
         * @param deltaTime The time in between the previous frame and this frame.
         */
        void updateArc(double deltaTime);
        /**
         * Updates the position of the point light. (Implemented by subclasses)
         * @param deltaTime The time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down. 
         * @param player The player of the game.
         */
        virtual void updatePos(double deltaTime,  bool* keyPressed, bool* keyHeld, Instance* player){};
    public:
        /**
         * Creates a new firefly.
         * @param X The center x-coord of the firefly in map coords.
         * @param Y The center y-coord of the firefly in map coords.
         * @param l The arc that represents the light that the firefly emits.
         */
        PointLight(double X, double Y, Arc* l);
        /**
         * Draws the point and sets up the arc to be drawn.
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         * @param layer The layer that is currently being drawn to.
         */
        void draw(GLDraw* gld, GLShaders* gls, int layer);
        /**
         * Updates the object; Calls updatePos and then updateArc.
         * @param deltaTime The time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down. 
         * @param player The player of the game.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        /// @return The arc that's associated with the player light.
        Arc* getLight();
};

#endif