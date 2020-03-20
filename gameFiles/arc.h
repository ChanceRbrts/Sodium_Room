#ifndef dos_obj_arc
#define dos_obj_arc

#include "../main/shaderBox.h"

class Arc{
    protected:
        ShaderBox* shade;
        double x, y, r;
        double rCol, gCol, bCol;
        double maxR;
        double d1, d2;
    public:
        Arc(double X, double Y, double R, double D1, double D2);
        ~Arc();
        double getX(){return x;};
        double getY(){return y;};
        void setPosition(double X, double Y);
        double getR(){return r;};
        void setR(double R);
        double getD1(){return d1;};
        double getD2(){return d2;};
        void setAngle(double D1, double D2);
        void draw(GLUtil* glu);
};

#endif