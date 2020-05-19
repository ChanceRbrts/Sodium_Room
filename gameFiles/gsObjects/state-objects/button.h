#ifndef dwr_state_button
#define dwr_state_button
#include "../../instance.h"

class Button : public Instance {
    protected:
        int pressed;
        bool multiPress, pressDown;
        std::string pressedVal;
        virtual void changeState();
        void setUp(int dir);
    public:
        Button(double X, double Y, int direction, std::string pressedValue);
        Button(double X, double Y, int direction, std::string pressedValue, bool multiPressed);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        // void draw(GLDraw* gld, GLShaders* gls);
        void collided(Instance* o, double deltaTime);
        void makePermanent();
};

#endif