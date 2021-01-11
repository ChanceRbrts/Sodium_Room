#version 120

uniform float camX;
uniform float camY;
uniform float width;
uniform float height;

vec4 stars(float cutoff, float depth){
    float con = 4589439;
    // Get the coordinates into a -10 to 10 field.
    vec2 coord = (gl_FragCoord.xy+vec2(floor((camX+con)/depth)-width/2, floor((camY+con)/depth))-height/2)/width*20;
    // Stars move very slowly compared to the player.
    float cX = coord.x;
    float cY = coord.y;
    // Do a random generator to make the stars.
    float alpha = fract(pow(abs(tan(pow(mod(cY, 10000), 2))*sin(cX)), 2.101)
                       +pow(abs(tan(pow(mod(cX, 10000), 2))*cos(cY)), 5.1891));
    float trueAlpha = 0*float(alpha<cutoff)+((alpha-cutoff)/(1-cutoff))*float(alpha>=cutoff);
    return vec4(1, 1, 1, trueAlpha);
}

vec4 clouds(float cutoff, float depth){
    float con = 823590;
    vec2 coord = (gl_FragCoord.xy+vec2(floor((camX+con)/depth)-width/2, floor((camY+con)/depth)-height/2))/width*20;
    float cX = coord.x;
    float cY = coord.y;
    // 
    float rand = 0;
    return vec4(1, 1, 1, 1);
}

void main(void){
    gl_FragColor = vec4(0.1, 0.1, 0.1, 1);
}