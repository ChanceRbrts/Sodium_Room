#version 120

uniform float xScale;
uniform float yScale;
uniform float camX;
uniform float camY;
uniform float time;
uniform bool horizontal;
uniform float open;

void main(void){
    float realX = gl_FragCoord.x*xScale-camX;
    float realY = (480-gl_FragCoord.y)*yScale-camY;
    float diamondX = mod(realX+32-64*time*float(horizontal), 64)-32;
    float diamondY = mod(realY+32-64*time*float(!horizontal), 64)-32;
    float manDist = abs(diamondX)+abs(diamondY);
    if (manDist > 48*open) discard;
    gl_FragColor = gl_Color;
}