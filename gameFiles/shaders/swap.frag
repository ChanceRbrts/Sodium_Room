#version 120

uniform float quadLU;
uniform float quadRU;
uniform float quadLD;
uniform float quadRD;

// 1 = LU, 2 = RU, 3 = LD, 4 = RD
void main(void){
    float relX = gl_TexCoord[0].x%0.5;
    float relY = gl_TexCoord[0].y%0.5;
    bool xB = x < 0.5;
    bool yB = y < 0.5;
    int u = quadLU*float(xB)*float(yB)+quadRU*float(!xB)*float(yB);
    int d = quadLD*float(xB)*float(!yB)+quadRU*float(!xB)*float(!yB);
    int rs = u+d;
    float x = 0.5*(u%2);
    float y = 0.5*(u-u%2)/2;
    gl_FragColor = texture2D(tex, vec2(relX, relY));
}
