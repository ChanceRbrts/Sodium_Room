#version 120

uniform float r;
uniform float g;
uniform float b;
uniform bool mono;
uniform sampler2D tex;

void main(void){
    vec4 sCol = gl_Color*texture2D(tex, gl_TexCoord[0].xy);
    float weight = r+g+b;
    float trueCol = sCol.r*r/weight+sCol.g*g/weight+sCol.b*b/weight;
    vec4 col1 = vec4(trueCol*r, trueCol*g, trueCol*b, 1);
    vec4 col = vec4(r, g, b, 1)*sCol;
    gl_FragColor = col1*float(mono)+col*float(!mono);
}
