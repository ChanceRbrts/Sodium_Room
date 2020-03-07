#version 120

varying vec2 texs;
uniform sampler2D tex;

void main(void){
    gl_FragColor = vec4(1) * texture2D(tex, texs);
}
