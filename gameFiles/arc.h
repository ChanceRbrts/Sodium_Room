#ifndef dos_obj_arc
#define dos_obj_arc

#include "../main/shaderBox.h"
#include <math.h>

struct ArcInfo{
    int id;
    double r, g, b;
};

class Arc{
    protected:
        ShaderBox* shade;
        double x, y, r;
        double rCol, gCol, bCol;
        double maxR;
        double d1, d2;
        bool connected;
    public:
        Arc(double X, double Y, double R, double D1, double D2, double RC, double GC, double BC);
        ~Arc();
        void changeConnection(bool c){ connected = c; }
        double getX(){return x;};
        double getY(){return y;};
        void setPosition(double X, double Y);
        double getR(){return r;};
        void setR(double R);
        double getD1(){return d1;};
        double getD2(){return d2;};
        ShaderBox* getShaderBox(){ return shade; }
        void setAngle(double D1, double D2);
        void draw(GLUtil* glu);
        ArcInfo getInfo(int id);
};

#endif