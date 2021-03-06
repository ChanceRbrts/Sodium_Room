#version 120

uniform float visible; // visible goes from 0 to 1
uniform float cyclePoint; // cyclePoint goes from 0 to 2

void main(void){
    // Small wire color if visibility is 0.
    vec3 basePoint = vec3(0.2, 0.2, 0.2);
    // Wrap the texture ID around to get the real texture X.
    float rTX = mod(gl_TexCoord[0].x+cyclePoint/2, 1);
    float PI = 3.14159265358979323846264338;
    // Sine wave rainbow for background color.
    // Red from 2/3 to 1/3, cenetred at 0
    float redInt = (cos(PI*rTX*1.5)*float(rTX < 1/3.0))+(cos(PI*(rTX-1)*1.5)*float(rTX > 2/3.0));
    float redCol =  gl_Color.r*redInt;
    // Green from 0 to 2/3, centered at 1/3.
    float greenCol = gl_Color.g*cos(PI*(rTX-1/3.0)*1.5)*float(rTX < 2/3.0);
    // Blue from 1/3 to 1, cenetered at 2/3.
    float blueCol = gl_Color.b*cos(PI*(rTX-2/3.0)*1.5)*float(rTX > 1/3.0);
    // Now, the color of this depends on the y texture coordinates.
    // Anything close to the center will have a wire color that glows first.
    float tY = gl_TexCoord[0].y;
    float cTY = 7.5/16;
    vec3 wireOff = basePoint*(0.25-visible)*float(visible < 0.25);
    vec3 wireOn = vec3(redCol, greenCol, blueCol)*((visible*4)*float(visible < 0.25)+1*float(visible >= 0.25));
    vec4 wireColor = vec4((wireOff+wireOn), 1)*float(abs(tY-cTY) < 0.75/16 && gl_TexCoord[0].x > 3/116.0 && gl_TexCoord[0].x < 112/116.0);
    // Everything else will just have a glow color that radiates from the wire.
    float texDiff = sin(PI/2*((visible-0.25)/0.75-abs(tY-cTY)/cTY));
    float wireAlpha = min(max(texDiff, 0), 1)*float(visible >= 0.25);
    vec4 glowColor = vec4(redCol, greenCol, blueCol, wireAlpha)*float(abs(tY-cTY) > 0.75/16 || gl_TexCoord[0].x <= 3/116.0 || gl_TexCoord[0].x >= 112/116.0);
    vec4 trueColor = wireColor+glowColor;
    // There should also be kind of a white glow near the center as the visibility 
    /*float wDif = 1/4*visible-abs(tY-cTY);
    float whiteAlpha = 4*wDif*float(abs(tY-cTY) < 1/4.0*visible);*/
    vec4 fullColor = trueColor;
    gl_FragColor = fullColor;
}