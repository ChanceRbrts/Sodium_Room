#version 120

uniform sampler2D tex;
uniform float x;
uniform float endX;

void main(void){
   float PI = 3.14159265358979323846264338;
   // 1 width to actually display, with 0.5 width being the shaderbox length;
   // 3.5 width, starting with 0.5 width to get our pixels.
   // So our width should be 4;
   // This is assuming a 4 width/1 height map.
   // What's actually in there.
   if (gl_TexCoord[0].x < 0.375 || gl_TexCoord[0].x > 0.625){
      discard;
   }
   float fakeX = gl_TexCoord[0].x*4;
   vec4 trueCol = texture2D(tex, gl_TexCoord[0].xy);
   vec2 cenCoord = vec2(fakeX-2, gl_TexCoord[0].y-0.5);
   // The y position is the distance from the center.
   float dist = sqrt(pow(cenCoord.x, 2)+pow(cenCoord.y, 2));
   if (dist > 0.5) dist = 0.5;
   // The x position is how far along we are in the circle.
   // We want -pi/pi to be (0, -1) and -pi/2 to be (-1, 0).
   float arc = (2+atan(cenCoord.x, -cenCoord.y)/2);
   float trueArc = arc/4;
   // Let's determine if we need a pixel at this point.
   float arc1 = 4-x;
   float arc2 = endX-x+2;
   gl_FragColor = texture2D(tex, vec2(trueArc, 0.5-dist));
   // Have the ends "wrap" around.
   if ((fakeX <= 2 && arc1 > arc) || (fakeX >= 2 && arc2 < arc)){
      float a1 = min(arc1, 2)*float(fakeX <= 2)+max(arc2, 2)*float(fakeX >= 2);
      float angle = (a1-2)*2;
      //vec2 pos = vec2((fakeX-2+2)/4, gl_TexCoord[0].y);
      vec2 pos = vec2((fakeX-2), gl_TexCoord[0].y-0.5);
      vec2 rotPos = vec2(pos.x*cos(angle)+pos.y*sin(angle), -pos.x*sin(angle)+pos.y*cos(angle));
      vec2 truePos = vec2((rotPos.x+a1)/4, rotPos.y+0.5);
      gl_FragColor = texture2D(tex, truePos);
   }
}
