#version 120

uniform sampler2D tex;

void main(void){
   gl_FragColor = 1-(gl_Color*texture2D(tex, gl_TexCoord[0].xy));
}
