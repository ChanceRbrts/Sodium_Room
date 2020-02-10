#version 120

// Get our translations of x and y.
uniform float xScale;
uniform float yScale;
uniform float camX;
uniform float camY;
uniform float time;
uniform bool horizontal;

void main(void){
    // So (camX, camY is at -1, 1)
    float realX = gl_FragCoord.x*xScale-camX;
    float realY = (480-gl_FragCoord.y)*yScale-camY;
    float check = realX*float(horizontal)+realY*float(!horizontal)-64*time;
    if (mod(check, 64.0) > 48) discard;
    gl_FragColor = gl_Color;
}
