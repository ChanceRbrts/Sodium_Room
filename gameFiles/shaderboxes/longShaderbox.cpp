#include "longShaderbox.h"

LongShaderbox::LongShaderbox(double X, double xPoint, double Y, double drawW, double endW, double H, 
        std::string vertShader, std::string fragShader, GLUtil* glu) 
        : ShaderBox(X, Y, drawW, H, vertShader, fragShader, glu){
    firstX = x;
    xScrollStart = (x+xPoint)*32;
    xScrollEnd = (x+endW)*32;
    drawX = 0;
    follow = true;
    uX = x;
    uniforms["endX"] = (xScrollEnd-firstX)/glu->draw->getWidth();
}

void LongShaderbox::moveShaderBox(double X, double Y, bool movingLevel){
    if (movingLevel){
        firstX += X-x;
        xScrollStart += X-x;
        xScrollEnd += X-x;
        x = X;
        uX = (X-firstX)/glu->draw->getWidth();
        y = Y;
        return;
    }
    if (X <= xScrollStart) X = xScrollStart;
    else if (X >= xScrollEnd) X = xScrollEnd; 
    x = X-xScrollStart+firstX;
    uniforms["x"] = (X-firstX)/glu->draw->getWidth();
    uX = (X-firstX)/glu->draw->getWidth();
    // Move the arc shaderboxes to the current position.
    if (arcOne == nullptr) return;
    arcOne->moveShaderBox(x, y, movingLevel);
    arcOneAlpha->moveShaderBox(x, y, movingLevel);
    arcTwo->moveShaderBox(x, y, movingLevel);
    arcTwoAlpha->moveShaderBox(x, y, movingLevel);
}

void LongShaderbox::resetUniforms(){
    uniforms["x"] = uX;
}

GravityWell::GravityWell(double X, double Y, double endPoint, GLUtil* glu)
    : LongShaderbox(X-glu->draw->getWidth()/16, glu->draw->getWidth()/16, Y, 
                    glu->draw->getWidth()/8, endPoint, glu->draw->getHeight()/32,
                    "", "gravityWell", glu){}
