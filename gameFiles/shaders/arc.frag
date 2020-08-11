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
uniform float a;
uniform bool mono;
uniform sampler2D tex;
uniform sampler2D prevTex;

void main(void){
    float tPI = 6.28318530718;
    // Convert world coordinates of the fragment into texture coordinates.
    float realX = gl_FragCoord.x*xScale+camX;
    float realY = (480-gl_FragCoord.y)*yScale+camY;
    // Get the distance from this fragment and the center of the arc.
    float distX = realX-x;
    float distY = realY-y;
    float fullDist = sqrt(distX*distX+distY*distY);
    // Get a degree in radians from the center.
    float d1X = d1 - tPI/48;
    float d2X = d2 + tPI/48;
    float d = atan(distY, distX);
    // Make sure D2 is always greater than d1.
    float D2 = d2;
    D2 += tPI*float(d2 <= d1);
    d2X += tPI*float(d2 <= d1);
    d += tPI*float(d < d1X && d2 <= d1);
    if (fullDist > rad*1.1 || d1X > d || d2X < d) discard;
    // Get the opaqueness of this fragment of the arc.
    float alpha = 1;
    alpha -= (d1-d)/(d1-d1X)*float(d < d1);
    alpha -= (d-D2)/(d2X-D2)*float(d > D2);
    alpha -= (fullDist-rad)/(rad*.1)*float(fullDist > rad);
    alpha *= a;
    vec4 sCol = gl_Color*texture2D(tex, gl_TexCoord[0].xy);
    // Get both the monochrome color and the tinted color.
    float weight = r+g+b;
    float trueCol = sCol.r*r/weight+sCol.g*g/weight+sCol.b*b/weight;
    vec4 col1 = vec4(trueCol*r, trueCol*g, trueCol*b, alpha);
    vec4 col = vec4(r, g, b, alpha)*sCol;
    // Get the color of the fragment we need to add to the arc-ed shaderbox.
    vec4 toAdd = col1*float(mono)+col*float(!mono);
    vec4 prevC = gl_Color*texture2D(prevTex, gl_TexCoord[0].xy);
    // Colors are added in proportionally to their alpha values.
    float newA = toAdd.a+prevC.a;
    vec4 newVal = (toAdd*toAdd.a+prevC*prevC.a)/newA;
    newA = 1*float(newA > 1)+newA*float(newA <= 1);
    newVal.a = newA;
    // vec4 rPrevC = vec4(prevC.r*prevC.a, prevC.g*prevC.a, prevC.b*prevC.a, prevC.a);
    gl_FragColor = newVal;
}