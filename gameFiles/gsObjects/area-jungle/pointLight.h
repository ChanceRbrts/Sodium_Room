#ifndef dwr_jungle_firefly
#define dwr_jungle_firefly

#include "../../instance.h"

class PointLight : public Instance{
    protected:
        Arc* light;
        double wide, maxWide, maxRadius;
        void (*updatePos)(double, PointLight*);
        void updateArc(double deltaTime);
    public:
        /**
         * Creates a new firefly.
         * @param X The center x-coord of the firefly in map coords.
         * @param Y The center y-coord of the firefly in map coords.
         * @param l The arc that represents the light that the firefly emits.
         * @param upd The function that updates the firefly.
         */
        PointLight(double X, double Y, Arc* l, void (*upd)(double, PointLight*));
        void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        /**
         * The default behavior for the firefly. By default, this is nothing.
         * @param deltaTime The time in seconds since the previous frame.
         * @param me The firefly that's calling the function.
         */
        void defaultBehavior(double deltaTime, PointLight* me);
};

#endif