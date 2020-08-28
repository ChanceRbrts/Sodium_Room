#version 120

uniform sampler2D tex;

void main(void){
   // gl_FragColor = vec4(gl_Color*texture2D(tex, gl_TexCoord[0].xy)r, 0, 0, 1);
   gl_FragColor = 1-vec4(vec4(gl_Color*texture2D(tex, gl_TexCoord[0].xy)).rgb, 0);
}
