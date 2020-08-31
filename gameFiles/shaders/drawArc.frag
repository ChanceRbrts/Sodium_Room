#version 120

uniform sampler2D tex;
uniform sampler2D alphaTex;

void main(void){
    vec4 mainCol = texture2D(tex, gl_TexCoord[0].xy);
    vec4 alphaCol = texture2D(alphaTex, gl_TexCoord[0].xy);
    gl_FragColor = vec4(mainCol.xyz, alphaCol.r);
}
