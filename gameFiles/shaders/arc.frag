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
uniform float xScale;
uniform float yScale;
uniform float r;
uniform float g;
uniform float b;
uniform bool mono;
uniform sampler2D tex;

void main(void){
    float tPI = 6.28318530718;
    float realX = gl_FragCoord.x*xScale-camX;
    float realY = (480-gl_FragCoord.y)*yScale-camY;
    float distX = realX-x;
    float distY = realY-y;
    float fullDist = sqrt(distX*distX+distY*distY);
    float d1X = d1 - tPI/48;
    float d2X = d2 + tPI/48;
    float d = atan(distY, distX);
    float D2 = d2;
    D2 += tPI*float(d2 <= d1);
    d2X += tPI*float(d2 <= d1);
    d += tPI*float(d < d1X && d2 <= d1);
    if (fullDist > rad*1.10 || d1X > d || d2X < d) discard;
    float alpha = 1;
    alpha -= (d1-d)/(d1-d1X)*float(d < d1);
    alpha -= (d-D2)/(d2X-D2)*float(d > D2);
    alpha -= (fullDist-rad)/(rad*.1)*float(fullDist > rad);
    vec4 sCol = gl_Color*texture2D(tex, gl_TexCoord[0].xy);
    float weight = r+g+b;
    float trueCol = sCol.r*r/weight+sCol.g*g/weight+sCol.b*b/weight;
    vec4 col1 = vec4(trueCol*r, trueCol*g, trueCol*b, alpha);
    vec4 col = vec4(r, g, b, alpha)*sCol;
    gl_FragColor = col1*float(mono)+col*float(!mono);
}