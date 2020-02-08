/**
 * Created by Chance Roberts, 7/14/2019
 * Modified by Chance Roberts, 8/16/2019
 * Moved to main because the editor and the game files both use this file.
 */

#ifndef dos_game_shader_box
#define dos_game_shader_box

#include "../glutils/glUtil.h"
#include <map>

/**
 * This is an abstraction of a frame buffer.
 * This frame buffer draws stuff onto itself as well as on the main screen.
 * From there, it draws the frame buffer onto the screen if it's on the screen.
 * With this, you can apply a shader to the entire area, as if you're processing an image.
 * Honestly, with GLUtil attached to this, I probably could have written this cleaner...
 */
class ShaderBox{
   protected:
      double x, y, w, h;
      double xOffset, yOffset;
      unsigned int frameID, texID, renID;
      std::map<std::string, float> uniforms;
      std::string fullID, solidID, drawID;
      GLUtil* glu;
   public:
      /**
       * Creates a frame buffer that draws within dimensions specified and applies shaders to them.
       * (Coordinates are in unit coordinates (Multiplied by 32 pixels))
       * @param X The left-most bound of the frame buffer.
       * @param Y The right-most bound of the frame buffer.
       * @param W The width of the frame buffer.
       * @param H The height of the frame buffer.
       * @param vertShader The vertex shader that we put the frame buffer under.
       * @param fragShader The fragment shader that we put the frame buffer under.
       * @param GLU The GLUnit that we bind to this frame buffer.
       */
      ShaderBox(double X, double Y, double W, double H, std::string vertShader, std::string fragShader, GLUtil* GLU);
      // Deconstructor.
      virtual ~ShaderBox();
      // Tells the engine to draw to this frame buffer.
      void drawOnBox();
      // Tells the engine to stop drawing to this frame buffer.
      void drawOutBox();
      // Draw the frame buffer to the screen.
      void draw();
      // Draw a red sqaure where the frame buffer would be. (Used for debugging)
      void drawBoundary();
      /**
       * 
       */
      virtual void moveShaderBox(double X, double Y);
      /**
       * Offsets where the frame buffer is actually drawn when you draw it.
       * @param xoffset How many pixels right the frame buffer actually draws itself to.
       */
      void setXOffset(double xoffset);
      /**
       * Offsets where the frame buffer is actually drawn when you draw it.
       * @param yoffset How many pixels down the frame buffer actually draws itself to.
       */
      void setYOffset(double yoffset);
};
#endif