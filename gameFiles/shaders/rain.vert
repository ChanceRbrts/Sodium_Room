#version 120

// Rain Box Dimensions (x+y in OpenGL coords, w+h in relative OpenGL coords)
uniform float x;
uniform float y;
uniform float w;
uniform float h;
// Units
uniform float unitX;
uniform float unitY;
// Terminal Velocity (For falling rain)
uniform float termV;
// Current Time (Assumption: 0 < time < 5)
uniform float time;

void main(void){
    vec4 pos = gl_Vertex;
    // The position of this is given by these variables;
    // x is the position of a rain drop (from 0-1)
    // y is the position of where that rain is (1=top, 0=bottom)
    // z is the offset time (in seconds) for when that rain drops (0-5)
    float trueX = x+pos.x*w;
    // We assume that if a rain drop is at max 24 pixels tall.
    // As such, if it's moving at max velocity, this should be 24 pixels away.
    float rainOff = 24/termV;
    // Unfortunately, we need to calculate both the top and the bottom...
    // This determines whether or not the rain drop is visible.
    // dTime is the time at the bottom of the raindrop; uTime is the time at the top of the raindrop.
    float dTime = mod(time+pos.z+0.5, 5)-0.5;
    float uTime = mod(time+pos.z-rainOff+0.5, 5)-0.5;
    // Now, we need to calculate where this is...
    // NOTE: Our acceleration is always 1024 pixels/second.
    float curVelD = min(termV, 1024*dTime);
    float curVelU = min(termV, 1024*uTime);
    // Determine the time accounted for before terminal velocity kicks in.
    float mTimeD = min(dTime, termV/1024);
    float aTimeU = min(0, min(uTime, termV/1024));
    // If a portion of the raindrop is above y, let's clip it to y. (Equivalent to t = 0)
    float aTimeD = min(0, mTimeD);
    // Determine the y-pixel given by the acceleration before terminal velocity.
    float trueYD = 1/2*1024*aTimeD*aTimeD+curVelD*aTimeD;
    float trueYU = 1/2*1024*aTimeU*aTimeU+curVelU*aTimeU;
    // Add the y-pixel change from the time at terminal velocity.
    trueYD += termV*max(0, dTime-termV/1024);
    trueYU += termV*max(0, uTime-termV/1024);
    // From the y position of our point, we know if it's the top or the bottom of the raindrop.
    float yToUse = trueYU*float(pos.y > 0.1) + trueYD*float(pos.y < 0.1);
    // h is guaranteed to be negative in this use case.
    yToUse = max(y+h, y+yToUse*unitY);
    // Rain is visible; Let's make sure to draw with z=0 and with the appropriate x and y values.
    vec4 inSight = vec4(trueX*pos.w, yToUse*pos.w, 0, pos.w);
    // Rain is not visible in this case.
    vec4 outOfSight = vec4(-999, -999, -999, 1);
    gl_FrontColor = gl_Color;
    gl_Position = gl_ModelViewProjectionMatrix*inSight*float(dTime > 0 || trueYU < y+h);
}
