#version 120

uniform float x;
uniform float y;
uniform float rad;
uniform float d1;
uniform float d2;
uniform float camX;
uniform float camY;
uniform float unitX;
uniform float unitY;
uniform float r;
uniform float g;
uniform float b;

void main(void){
    float tPI = 6.28318530718
    float realX = gl_FragCoord.x*xScale-camX;
    float realY = (480-gl_FragCoord.y)*yScale-camY;
    float distX = realX-x;
    float distY = realY-y;
    float fullDist = sqrt(distX*distX+distY*distY);
    float d = atan(distY, distX);
    d2 += tPI*float(d2 <= d1);
    d += tPI*float(d < d1 && d2 <= d1);
    bool dis = fullDist > rad && (d1 > d || d2 < d);
    if (dis) discard;
        
}