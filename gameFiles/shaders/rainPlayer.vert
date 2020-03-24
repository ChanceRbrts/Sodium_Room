#version 120

// Rain Box Dimensions
uniform float x;
uniform float y;
// Units
uniform float unitX;
uniform float unitY;
// Terminal Velocity (For falling rain)
uniform float termV;
// Current Time (Assumption: 0 < time < 5)
uniform float time;
uniform float maxTime;
uniform bool gravityDown;


void main(void){
    vec4 pos = gl_Vertex;
    float trueX = x+pos.x*unitX;
    // Same as the rain shader, we need to determine where our y position really is.
    float trueTime = max(0, min(maxTime, time-pos.z));
    float objTime = min(maxTime, time);
    // We still do need to calculate two different positions to subtract them to get our actual position.
    // As usual, the acceleration is 1024 pixels/second.
    float curVelTrue = min(termV, trueTime*1024);
    float curVelObj = min(termV, objTime*1024);
    float accTimeTr = min(trueTime, termV/1024);
    float accTimeObj = min(objTime, termV/1024);
    float dropTimeTr = max(0, trueTime-termV/1024);
    float dropTimeObj = max(0, objTime-termV/1024);
    // Move it down (For some reason, we don't need the velocity when calculating this distance?)
    float trueY = 0.5*1024*accTimeTr*accTimeTr+0*curVelTrue*accTimeTr;
    float objY = 0.5*1024*accTimeObj*accTimeObj+0*curVelObj*accTimeObj;
    //float trueY = 0.25*512*accTimeTr*accTimeTr+curVelTrue*accTimeTr/4;
    //float objY = 0.25*512*accTimeObj*accTimeObj+curVelObj*accTimeObj/4;
    // Add our terminal velocity in...
    trueY += termV*dropTimeTr;
    objY += termV*dropTimeObj;
    // And find the difference! (Negative if falling down, Positive if falling up)
    trueY = (trueY-objY)*(-1+2*float(gravityDown));
    // trueY = y + (pos.y-pos.z*64)*unitY;
    trueY = y+(trueY+pos.y)*unitY;
    gl_FrontColor = gl_Color;
    gl_Position = gl_ModelViewProjectionMatrix*vec4(trueX*pos.w, trueY*pos.w, 0, pos.w);
}