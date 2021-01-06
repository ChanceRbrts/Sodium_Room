#version 120

uniform float camX;
uniform float camY;
uniform float width;
uniform float height;

vec4 stars(float cutoff, float depth){
    float con = 4589439;
    // Get the coordinates into a -10 to 10 field.
    vec2 coord = (gl_FragCoord.xy+vec2(floor((camX+con)/depth), floor((camY+con/depth))-width/2))/width*20;
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
    vec2 coord = (gl_FragCoord.xy+vec2(floor((camX+con)/depth), floor((camY+con/depth))-width/2))/width*20;
    float cX = coord.x;
    float cY = coord.y;
    // 
    float rand = 0;
    return vec4(1, 1, 1, 1);
}

void main(void){
    vec4 backColor = vec4(0, 0, 0, 1);
    // Create the stars
    vec4 star = stars(0.999, 100);
    vec4 star2 = stars(0.999, 50);
    vec4 star3 = stars(0.999, 20);
    vec4 star4 = stars(0.999, 10);
    vec4 star5 = stars(0.999, 5);
    // Do alpha blending.
    vec4 starCol = vec4(backColor.xyz*(1-star.a)+star.xyz*star.a, 1.0);
    vec4 star2Col = vec4(starCol.xyz*(1-star2.a)+star2.xyz*star2.a, 1.0);
    vec4 star3Col = vec4(star2Col.xyz*(1-star3.a)+star3.xyz*star3.a, 1.0);
    vec4 star4Col = vec4(star3Col.xyz*(1-star4.a)+star4.xyz*star4.a, 1.0);
    vec4 star5Col = vec4(star4Col.xyz*(1-star5.a)+star5.xyz*star5.a, 1.0);
    gl_FragColor = star5Col;
}