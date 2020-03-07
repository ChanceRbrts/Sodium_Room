#version 120

// Get related positions. (Both of these are the centers of the objects)
uniform float playerX;
uniform float playerY;
uniform float x;
uniform float y;
// Get our translations of x and y.
uniform float unitX;
uniform float unitY;
uniform float displayX;
uniform float displayY;
uniform float time;
attribute float offset;
attribute vec2 texture;
// If true, make floor go away when player is far rather than near.
uniform bool proximity;

varying vec2 texs;

void main(void){
    float PI = 3.14159265358979323846264338;
    // x and y are positions, z is behavior.
    vec4 pos = gl_Vertex;
    float xDist = playerX-x;
    float yDist = playerY-y;
    float distAway = sqrt(xDist*xDist+yDist*yDist);
    // 48 Pixels Away is completely there.
    // 96 Pixels Away is starting to come together.
    // 128 Pixels Away is completely apart.
    // 0.001 to prevent some undefined behavior.
    float d1 = max(0.001, min(distAway-80, 100));
    float d2 = max(0.001, 80-distAway);
    float radius1 = pow(d1/48, 2)*float(d1 < 1)+pow(d1/48, 4)*float(d1 >= 1);
    // 64 * 64 = 4096
    float radius2 = pow(d2/40, 2);
    float radius = radius1*float(proximity)+radius2*float(!proximity);
    // Now, we need to do particle movement.
    // Values are from 0-31, so 0-15 should go left and 16-31 should go right.
    float xPos = (pos.x-15.5)/32;
    float yPos = (pos.y-15.5)/32;
    float xPosAdd = 0;
    float yPosAdd = 0;
    float zBit = mod(pos.z, 1);
    float sinTimes = (1/8+1*zBit)*PI;
    // Behaviors are basically sine wave stuff.
    // Behavior 1: Moves in a circle around spot.
    // Behavior 2: Moves in a horizontal line(-ish) around spot.
    // Behavior 3: Moves in a vertical line(-ish) around spot.
    // Since this is a float, the decimal point determines the speed of the circle.
    xPosAdd = 0.4*cos(sinTimes*(time+offset))*float(pos.z >= 0 && pos.z < 2);
    yPosAdd = 0.4*sin(sinTimes*(time+offset))*float((pos.z >= 0 && pos.z < 1) || (pos.z >= 2 && pos.z < 3));
    yPosAdd += 0.05*cos(3*sinTimes*(time+offset))*float(pos.z >= 1 && pos.z < 2);
    xPosAdd += 0.05*sin(3*sinTimes*(time+offset))*float(pos.z >= 2 && pos.z < 3);
    // Behavior 4 & 5: Sine wave shenanigans.
    float d1Add = 0.45*cos(sinTimes*(time+offset));
    float d2Add = 0.1*cos(sinTimes*(time+offset))*cos(19/4*sinTimes*(time+offset));
    xPosAdd += d1Add*float(pos.z >= 3 && pos.z < 4)+d2Add*float(pos.z >= 4 && pos.z < 5);
    yPosAdd += d2Add*float(pos.z >= 3 && pos.z < 4)+d1Add*float(pos.z >= 4 && pos.z < 5);
    // Now that we have our behaviors down, we need to calculate our base position.
    float baseX = pos.x+(xPos*radius+xPosAdd*radius)*16;
    float baseY = pos.y+(yPos*radius+yPosAdd*radius)*16;
    gl_FrontColor = gl_Color;
    float realX = displayX+baseX*unitX;
    float realY = displayY+baseY*unitY;
    texs = texture;
    gl_Position = gl_ModelViewProjectionMatrix*vec4(realX*pos.w, realY*pos.w, 0, pos.w);
}