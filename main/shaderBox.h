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
      /// Whether or not we need to remove the shaderbox.
      bool remove;
      /// Positional Variables
      double x, y, w, h;
      /// If we are drawing a view on some sort of offset, specify that here.
      double xOffset, yOffset;
      /// IDs for the framebuffer, the texture, and the renderbuffer for the frame buffer.
      unsigned int frameID, texID, renID;
      /// The uniforms that we use for the shader used.
      std::map<std::string, float> uniforms;
      /// The integer uniform that we use for the shader used.
      std::map<std::string, int> uniformIs;
      /// The IDs of the framebuffer.
      std::string fullID, solidID, drawID;
      /// Whether or not to follow the player.
      bool follow;
      /// The GLUtil to use to mess with the Shaderbox
      GLUtil* glu;
      /// Shaderbox used for drawing the arcs.
      ShaderBox* arcOne;
      /// Shaderbox corresponding to the opaqueness of the arcs.
      ShaderBox* arcOneAlpha;
      /// Shaderbox used for drawing the arcs (for multiple arcs).
      ShaderBox* arcTwo;
      /// Shaderbox corresponding to the opaqueness of the arcs. (For multiple arcs)
      ShaderBox* arcTwoAlpha;
      /// Whether or not alpha blending will be used when drawing the shaderbox.
      bool blend;
      /// Whether or not we can draw from the screen if part of the shaderbox is off the screen.
      bool fastDraw;
      /// Whether or not the shaderbox needs to be drawn before the arcs are drawn.
      bool drawBeforeArc;
      /// Whether or not any arc drawn to this shaderbox should be replaced with.
      bool replaceWithArc;
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
      /// Deconstructor.
      virtual ~ShaderBox();
      /// Tells the engine to draw to this frame buffer.
      void drawOnBox();
      /// Flags the shaderbox as needing to be removed.
      void removeMe();
      /// Show whether or not we can remove this object.
      bool canRemove(){ return remove; }
      /// Tells the engine to stop drawing to this frame buffer.
      void drawOutBox();
      /// Draw the frame buffer to the screen.
      void draw(double alpha = 1);
      /// Whether or not this shaderbox follows the player.
      bool followPlayer(){ return follow; }
      /// Draw a red sqaure where the frame buffer would be. (Used for debugging)
      void drawBoundary();
      /// @return Whether or not the shaderbox is on the current screen.
      bool canDraw();
      /// @return The x position of the shaderbox.
      double getX();
      /// @return The y position of the shaderbox.
      double getY();
      /**
       * Moves the shaderbox to a position.
       * @param X The left side of the shader box (in pixel coords)
       * @param Y The top side of the shader box (in pixel coords)
       * @param movingLevel Whether or not the level is being moved.
       */
      virtual void moveShaderBox(double X, double Y, bool movingLevel);
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
      /**
       * Adds a uniform value to the shader.
       * @param name The identifier of the uniform.
       * @param value The value of the uniform.
       */
      void addUniform(std::string name, float value);
      /**
       * Adds a uniform value to the shader.
       * This is an integer for the purposes of a sampler.
       * @param name The identifier of the uniform.
       * @param value The value of the uniform.
       */
      void addUniformI(std::string name, int value);
      /**
       * Clears the shader box to have every value be 0.
       */
      void clearBox();
      /// Clears the shaderboxes that correspond to drawing arcs.
      void clearArcBoxes();
      /// @return The texture ID of the shaderbox
      unsigned int getTextureID();
      /// @return The current ID of the shader.
      std::string getDrawID(){ return drawID; };
      /**
       * Changes the shader to an ID of a currently known shader.
       * @param dID The ID of a shader that has already been created.
       * @return Whether or not the shader has changed into the new shader.
       */
      bool changeShader(std::string dID);
      /**
       * Changes the shader to a program with a vertex and fragment shader.
       * @param vert The vertex shader to use.
       * @param frag The fragment shader to use.
       * @return Whether or not the shader has changed into the new shader.
       */
      bool changeShader(std::string vert, std::string frag);
      /**
       * Change whether or not the shaderbox should blend when drawing it.
       * @param blnd Whether or not blending should be used.
       */
      void setBlend(bool b);
      /// @param b Whether or not to draw this shaderbox before drawing arcs.
      void setDrawBeforeArc(bool b);
      /// @return Whether or not to draw this shaderbox before drawing arcs.
      bool getDrawBeforeArc(){ return drawBeforeArc; };
      /// @param b Whether or not to have an arc replace parts of the shaderbox.
      void setReplaceWithArc(bool b);
      /// @return Whether or not to have an arc replace parts of the shaderbox.
      bool getReplaceWithArc(){ return replaceWithArc; };
      /// @return Whether or not to use the screen to draw to the shaderbox.
      bool getFastDraw(){ return fastDraw; };
      /**
       * Sets whether or not the screen should draw to the shaderbox.
       * (NOTE: Set to true by default.)
       * The alternative is drawing everything to the shaderbox.
       * The downside to screen drawing is that if the shaderbox is 
       * partially off the screen, it could mess up the shaders when drawing
       * back to the screen.
       * Setting this to off causes it to draw only this level, though.
       * If another level's object overlaps with this shaderbox with this off,
       * it won't draw and could break some things.
       * @param fD Whether or not the screen should draw to the shaderbox.
       */
      void setFastDraw(bool fD);
      /// @return The shaderbox corresponding to the first box used to draw the arcs.
      ShaderBox* getArcOne(){ return arcOne; };
      /// @return The shaderbox corresponding to the transparency of the arcs.
      ShaderBox* getArcOneA(){ return arcOneAlpha; };
      /// @return The shaderbox corresponding to the first box used to draw the arcs.
      ShaderBox* getArcTwo(){ return arcTwo; }; 
      /// @return The shaderbox corresponding to the transparency of the arcs.
      ShaderBox* getArcTwoA(){ return arcTwoAlpha; };
      /**
       * Resets uniforms that might need resetting after loading different variables.
       */
      virtual void resetUniforms(){};
};

struct DualSBox{
   ShaderBox* first;
   ShaderBox* second;
};

#endif