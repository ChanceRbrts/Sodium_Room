#include "longShaderbox.h"

LongShaderbox::LongShaderbox(double X, double xPoint, double Y, double drawW, double endW, double H, 
        std::string vertShader, std::string fragShader, GLUtil* glu) 
        : ShaderBox(X, Y, drawW, H, vertShader, fragShader, glu){
    firstX = x;
    xScrollStart = (x+xPoint)*32;
    xScrollEnd = (x+endW)*32;
    drawX = 0;
    uniforms["endX"] = (xScrollEnd-firstX)/glu->draw->getWidth();
}

void LongShaderbox::moveShaderBox(double X, double Y){
    if (X > xScrollStart && X < xScrollEnd){
        x = X-xScrollStart+firstX;
    }
    uniforms["x"] = (X-firstX)/glu->draw->getWidth();
}

GravityWell::GravityWell(double X, double Y, double endPoint, GLUtil* glu)
    : LongShaderbox(X-glu->draw->getWidth()/16, glu->draw->getWidth()/16, Y, 
                    glu->draw->getWidth()/8, endPoint, glu->draw->getHeight()/32,
                    "", "gravityWell", glu){}
