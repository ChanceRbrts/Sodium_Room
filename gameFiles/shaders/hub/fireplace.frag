#version 120

// Dim with a brighter light at a center point.

uniform float backA;
uniform float fireA;
uniform float fireR;
uniform float fireX;
uniform float fireY;
uniform float camX;
uniform float camY;
uniform float h;
uniform sampler2D tex;

void main(void){
    vec4 sCol = gl_Color*texture2D(tex, gl_TexCoord[0].xy);
    float distX = fireX-(gl_FragCoord.x+camX);
    float distY = fireY-(h-gl_FragCoord.y+camY);
    float dist = sqrt(distX*distX+distY*distY);
    // float alpha = backA+fireA*sqrt((fireR-dist)/fireR)*float(dist < fireR);
    float alpha = backA+fireA*pow((fireR-dist)/fireR, 0.6)*float(dist < fireR);
    vec4 col = vec4(alpha, alpha, alpha, 1)*sCol; 
    gl_FragColor = col;
}
