#ifndef dwr_state_button
#define dwr_state_button
#include "../../instance.h"

class Button : public Instance {
    protected:
        int pressed, maxPress;
        bool multiPress, pressDown;
        int pressDir;
        std::string pressedVal;
        std::map<Instance*, bool> collWith;
        virtual void changeState();
        void setUp(int dir);
    public:
        Button(double X, double Y, int direction, std::string pressedValue);
        Button(double X, double Y, int direction, std::string pressedValue, int maxPressed);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        // void draw(GLDraw* gld, GLShaders* gls);
        void collided(Instance* o, double deltaTime);
        void makePermanent();
};

#endif