#ifndef dos_longShaderbox
#define dos_longShaderbox

#include "../../main/shaderBox.h"

class LongShaderbox : public ShaderBox{
    private:
        double firstX;
        double xScrollStart;
        double xScrollEnd;
        double drawX;
        double uX;
    public:
        LongShaderbox(double X, double xPoint, double Y, double drawW, double endW, double H, 
            std::string vertShader, std::string fragShader, GLUtil* glu);
        void moveShaderBox(double X, double Y);
        void resetUniforms();
};

class GravityWell : public LongShaderbox{
    public:
        GravityWell(double X, double Y, double endPoint, GLUtil* glu);
};

#endif