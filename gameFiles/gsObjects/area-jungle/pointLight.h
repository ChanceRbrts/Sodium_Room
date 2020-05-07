#ifndef dwr_jungle_firefly
#define dwr_jungle_firefly

#include "../../instance.h"

class PointLight : public Instance{
    protected:
        Arc* light;
        double wide, maxRadius;
        void updateArc(double deltaTime);
        virtual void updatePos(double deltaTime){};
    public:
        /**
         * Creates a new firefly.
         * @param X The center x-coord of the firefly in map coords.
         * @param Y The center y-coord of the firefly in map coords.
         * @param l The arc that represents the light that the firefly emits.
         */
        PointLight(double X, double Y, Arc* l);
        void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
        Arc* getLight();
};

#endif