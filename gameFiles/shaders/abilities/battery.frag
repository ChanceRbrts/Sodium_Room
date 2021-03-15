#version 120

uniform float r;
uniform float g;
uniform float b;
uniform float life;
// uniform float dLife;
uniform sampler2D texInt;
uniform sampler2D texExt;

void main(void){
    vec2 tex = gl_TexCoord[0].xy;
    // Get the color values of both the interior and the exterior first.
    // The interior color is then changed to the color of the battery.
    vec4 intCol = texture2D(texInt, tex)*vec4(r, g, b, 1);
    vec4 extCol = texture2D(texExt, tex);
    // Now, to determine whether or not the interior is visible...
    // The interior stretches from y=8 to y=23. (y=24 = 0 Life)
    float maxY = 3/4.0;
    float diffY = 1/2.0;
    // TODO: Make some pseudo-water effects?
    float intA = float(tex.y+life*diffY > maxY);
    intCol = vec4(intCol.xyz, intCol.a*intA);
    // Now, we blend the exterior texture on the interior texture!
    gl_FragColor = extCol.a*extCol+(1-extCol.a)*intCol;
}
