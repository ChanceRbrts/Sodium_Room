#ifndef dos_glUtil
#define dos_glUtil

#include <string>
#include <vector>

// Just consider this an enum for the controls...
// These headers were changed since they messed with SDL2... :|
#define BUTTON_LEFT 0
#define BUTTON_RIGHT 1
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_A 4
#define BUTTON_B 5
#define BUTTON_START 6
#define BUTTON_SELECT 7
#define BUTTON_END 8
// The length of the control array.
#define CON_LEN 10

// A struct of three ints. Useful in a few circumstances.
struct pointInt{
   int x; 
   int y;
   int z;
};

// (Added because C++11 may not like too many conversions.)
// A struct of three unsigned ints. Useful in a few circumstances.
struct upointInt{
   unsigned int x;
   unsigned int y;
   unsigned int z;
};

// A struct of three doubles. Useful only for camera translations.
struct pointDouble{
   double x;
   double y;
   double z;
};

// A struct of camera information; Used for Shaderboxes.
struct cameraMem{
   double x;
   double y;
   double w;
   double h;
   struct cameraMem* prev;
};

// A struct to put an int into a stack.
struct intStack{
   int x;
   struct intStack* prev;
};

/**
 * Handles the controls from our chosen Utility Toolkit
 * Everything is static since input is basically a Singleton.
 */
class GLControls{
   private: 
      static bool keyPressed[CON_LEN];
      static bool keyHeld[CON_LEN];
      /**
       * The ASCII keys that are used for the controls array.
       * Left = W, Right = D, Up = W, Down = S, A = X, B = Z, Start = Enter, Select = Space, End = Escape
       */
      static char keys[CON_LEN];
      /**
       * The Non-ASCII keys that are used for the controls array.
       * Left = Left Arrow, Right = Right Arrow, Up = Up Arrow, Down = Down Arrow
       */
      static int keysS[CON_LEN];
      static int mouseX, mouseY;
      static int mousePressed;
      static int mLeft, mRight, mCenter;
      // Information that is implementation based.
      void* extraInfo;
   public:
      /** 
       * Initializes the GLControls class.
       * @param eInfo The implementation specific information passed to the class.
       */
      GLControls(void* eInfo);
      static void controlLoop();
      static void keyDown(unsigned char ch, int x, int y);
      static void keyUp(unsigned char ch, int x, int y);
      static void specialKey(int key, int x, int y);
      static void specialKeyUp(int key, int x, int y);
      static void mouseFunc(int button, int state, int x, int y);
      static void mouseMotion(int x, int y);
      static void mousePassMotion(int x, int y);

      // Makes every key press and mouse click false.
      static void resetControls();

      // The next functions are constant regardless of implementation of the GLUtil classes.

      /**
       * Gets all of the held keys.
       * Because we are doing a simple game, this is just a 10-key array.
       * (See keys and keysS for more info.)
       */
      static bool* getKeyHeld(){return keyHeld;};
      /**
       * Gets all of the keys that were pressed that frame.
       * Because we are doing a simple game, this is just a 10-key array.
       * (See keys and keysS for more info.)
       */
      static bool* getKeyPressed(){return keyPressed;};
      // Gets the value for the left button on the mouse.
      static int mouseLeft(){return mLeft;};
      // Gets the value for the right button on the mouse.
      static int mouseRight(){return mRight;};
      // Gets the value for the middle button on the mouse.
      static int mouseCenter(){return mCenter;};

      /**
       * Gives you a struct of three integers giving you information on the mouse.
       * x -> The x position of the mouse on the window.
       * y -> The y position of the mouse on the window.
       * z -> The mouse button that has been clicked. (-1 if nothing.)
       */
      static pointInt getMouseInfo();
};

/**
 * Abstracts shader work and frame buffer work.
 */
class GLShaders{
   private:
      std::vector<int> programs;
      std::vector<std::string> programIDs;
      std::string getShaderType(int type);
      struct intStack* curFrameBuffer;
      struct intStack* curShader;
      // Information that is implementation based.
      void* extraInfo;
   public:
      /**
       * Constructor for the shader class.
       * @param eInfo The implementation specific information passed to the class.
       */
      GLShaders(void* eInfo);
      void addShaders(){};
      /**
       * Check if a shader pair (program) exists.
       * @param shaderID The ID of the shader pair.
       */
      bool programExists(std::string shaderID);
      /**
       * Creates a shader to use.
       * @param name The filename of the shader to use.
       * @param type The type of the shader. (Vert, Frag, etc.)
       */
      int createShader(std::string name, int type);
      /**
       * Creates a pair of shaders to use. (Vert Shader, Fragment Shader)
       * @param vertName The name of the vertex shader to use. (Without the .vert file extension)
       * @param fragName The name of the fragment shader to use. (Without the .frag file extension)
       * @param shaderID The ID of the program to move this into.
       */
      int createProgram(std::string vertName, std::string fragName, std::string shaderID);
      /**
       * Creates a pair of shaders to use.
       * This is a shortcut for if you have shaderID.vert and shaderID.frag.
       * @param shaderID The ID of the program. (And the names of the shaders to use.)
       */
      int createProgram(std::string shaderID){
         return createProgram(shaderID, shaderID, shaderID);
      }
      /**
       * Binds the shader program with the shaderID to the drawing command.
       * In practice, this actually pushes the shader onto a stack.
       * The first shader on that stack is then drawn.
       * @param shaderID The ID of the shader program to use.
       */
      int bindShader(std::string shaderID);
      /**
       * Binds the shader program with the shaderID to the drawing command.
       * In practice, this actually pushes the shader onto a stack.
       * The first shader on that stack is then drawn.
       * @param shaderID The REAL ID of the shader program to use. (At least in GLUT)
       */
      int bindShader(int shaderID);
      /**
       * Unbinds the current shader program and pops it off the stack.
       * If there is another shader program on the stack, it automatically binds that.
       */
      void unbindShader();
      /**
       * Creates a frame buffer and gives a struct with 3 ints.
       * x -> The frame buffer ID.
       * y -> The ID of the texture that the frame buffer is attached to.
       * z -> The ID of the render buffer/depth buffer that the frame buffer is attached to.
       */
      struct upointInt createFrameBuffer();
      /**
       * Changes the resolution of the frame buffer.
       * @param frame The frame buffer ID.
       * @param tex The texture ID that the frame buffer is attached to.
       * @param ren The render buffer/depth buffer ID that the frame buffer is attached to.
       */
      void resizeFrameBuffer(int frame, int tex, int ren, double w, double h);
      /**
       * Binds the frame buffer so all draw commands draw into the framebuffer.
       * In practice, this actually pushes the frame buffer onto a stack.
       * The top frame buffer is then the one that is drawn to.
       * @param frame The frame buffer ID
       */ 
      void bindFrameBuffer(int frame);
      /**
       * Unbinds the frame buffer, giving draw commands back to what was before.
       * If there was another frame buffer binded before this, it re-binds it.
       * Otherwise, all draw commands go back to the screen again.
       */
      void unbindFrameBuffer();
      /**
       * Delete the framebuffer. (Used for cleanup code.)
       * @param frame The frame buffer ID.
       * @param tex The texture ID that the frame buffer is attached to.
       * @param ren The render buffer/depth buffer ID that the frame buffer is attached to.
       */
      void deleteFrameBuffer(int frame, int tex, int ren);

      /**
       * Adds a uniform float value to the shader.
       * @param name The string of the uniform value.
       * @param uni The uniform value.
       */
      void addUniform(int program, std::string name, float uni);

      /**
       * Adds a uniform interger value to the shader.
       * @param name The string of the uniform value.
       * @param uni The uniform value.
       */
      void addUniformI(int program, std::string name, int uni);

      /**
       * Adds an attribute to the shader.
       * @param program The current shader.
       * @param att The attribute to add to the shader.
       * @param pointer The pointer to the array of attributes.
       * @param gap The gap of floats to use.
       * @return The int representation of that attribute.
       */
      int addAttribute(int program, std::string att, float* pointer, int gap);

      /**
       * Disable the attribute.
       * @param program The current shader.
       * @param att The attribute to remove.
       */
      void removeAttribute(int program, int att);

      // The next functions are constant regardless of implementation of the GLUtil classes.

      intStack* pushIntStack(intStack* is, int i);
      intStack* popIntStack(intStack* is);
};

/**
 * The Utility class to deal with generating textures.
 * This includes dealing with image files and fonts.
 */
class GLTextureGen{
   private:
      void* extraInfo;
   public:
      /** 
       * The constructor for the texture generation.
       * @param eInfo The implementation specific information passed to the class.
       */
      GLTextureGen(void* eInfo);
      /**
       * Loads an image from a file into a texture.
       * @param img The image file to load.
       */
      unsigned int loadImage(std::string img);
      /**
       * Loads a string into a texture.
       * Returns a point int that is (width, height, texture)
       * @param str The string to render.
       * @param font The font to render the string in.
       * @param r The red color to render the string (0-1)
       * @param g The green color to render the string (0-1)
       * @param b The blue color to render the string (0-1)
       */
      pointInt renderString(std::string str, std::string font, float r, float g, float b);
      /**
       * Points the path into the font that is to be used.
       * For this, it checks the thing.
       * @param font The font name.
       */
      std::string fontPath(std::string font);
      /**
       * Remove texture
       */
      void removeTexture(int tex);
};

/**
 * Deals with all of the draw commands.
 * Honestly, this class probably has far too many functions...
 */
class GLDraw{
   private:
      std::vector<float> vertices;
      std::vector<float> colors;
      std::vector<float> texts;
      struct cameraMem* headCam = nullptr;
      int maxVerts;
      int vert;
      double width, height;
      bool normalCalc;
      int mode;
      std::vector<float> tempVert;
      std::vector<float> tempCol;
      std::vector<float> tempTex;
      int toMode(std::string type);
      /// A helper function to resize the viewport when changing the camera stack.
      void resizeViewport();
      // Information that is implementation based.
      void* extraInfo;
   public:
      GLTextureGen* texGen;
      double camX, camY;
      /**
       * Initializes the draw command using the resolution of the screen.
       * @param wid The width of the screen in pixels.
       * @param hei The height of the screen in pixels.
       * @param eInfo The implementation specific information passed to the class.
       */
      GLDraw(double wid, double hei, void* eInfo);
      ~GLDraw();
      /**
       * Tells OpenGL to begin drawing. (Same as calling glBegin)
       * @param type What you actually want to draw (GL_QUADS, GL_TRIANGLES, etc.)
       */
      void begin(int type);
      /**
       * Tells OpenGL to begin drawing. (Same as calling glBegin)
       * Gives a string parameter to parse to avoid calling abstract GL constants.
       * @param type What you actually want to draw (QUADS, TRIANGLES, LINES, POINTS implemented)
       */
      void begin(std::string type);
      /**
       * Bind a texture to GL_TEXTURE0.
       * @param tex The ID of the texture.
       */
      void bindTexture(int tex){bindTexture(tex, 0, true);};
      /**
       * Binds a texture to the given texture layer.
       * (If you put it on a layer besides GL_TEXTURE0, the active texture will still be 0)
       * @param tex The ID of the texture.
       * @param texLayer The layer to bind on (GL_TEXTURE(X)) (Expected to be 0-9)
       */
      void bindTexture(int tex, int texLayer){bindTexture(tex, texLayer, true);};
      /**
       * Binds a texture to the given texture layer.
       * @param tex The ID of the texture.
       * @param texLayer The layer to bind on (GL_TEXTURE(X)) (Expected to be 0-9)
       * @param backToNormal Whether or not to move back to the GL_TEXTURE0 layer again.
       */
      void bindTexture(int tex, int texLayer, bool backToNormal);
      // Makes it so textures are now drawn.
      void enableTextures();
      // Makes it so textures are no longer drawn.
      void disableTextures();
      /**
       * Sets the color to draw. (Without transparent blending)
       * @param r The value for red. (0-1)
       * @param g The value for green. (0-1)
       * @param b The value for blue. (0-1)
       */
      void color(double r, double g, double b);
      /**
       * Sets the color to draw. (With transparent blending)
       * @param r The value for red. (0-1)
       * @param g The value for green. (0-1)
       * @param b The value for blue. (0-1)
       * @param a The value for transparency. (0=Transparent, 1=Opaque)
       */
      void color(double r, double g, double b, double a);
      /**
       * Sets the color to draw.
       * @param r The value for red. (0-1)
       * @param g The value for green. (0-1)
       * @param b The value for blue. (0-1)
       * @param a The value for transparency. (0=Transparent, 1=Opaque)
       * @param blend Whether or not to draw with transparent blending.
       */
      void color(double r, double g, double b, double a, bool blend);
      /**
       * Setting the texture coordinates to draw on a vertex.
       * @param s The x value of the texture (0-1)
       * @param t The y value of the texture (0-1)
       */
      void texCoords(double s, double t);
      /**
       * Draws a vertex in window coordinates.
       * @param v1 The x value to draw the vertex in window coords.
       * @param v2 The y value to draw the vertex in window coords.
       */
      void vertW(double v1, double v2){vertW(v1, v2, 0);};
      /**
       * Draws a vertex in window coordinates.
       * @param v1 The x value to draw the vertex in window coords.
       * @param v2 The y value to draw the vertex in window coords.
       * @param v3 The z value to draw the vertex in world coords.
       */
      void vertW(double v1, double v2, double v3){
         vertex((v1-camX)*2/width-1, 1-(v2-camY)*2/height, v3);
      }
      /**
       * Converts a point into a point on the window.
       * Only acts as translation; Does not draw this point.
       * @param v1 The x value to translate.
       * @param v2 The y value to translate.
       */
      pointDouble vPoint(double v1, double v2);
      /**
       * Draw a vertex in OpenGL coordinates.
       * @param v1 The x value to draw the vertex (-1 to 1, where 1 is right).
       * @param v2 The y value to draw the vertex (-1 to 1, where 1 is up).
       */
      void vertex(double v1, double v2){vertex(v1, v2, 0);};
      /**
       * Draw a vertex in OpenGL coordinates.
       * @param v1 The x value to draw the vertex (-1 to 1, where 1 is right).
       * @param v2 The y value to draw the vertex (-1 to 1, where 1 is up).
       * @param v3 The z value to draw the vertex in world coords.
       */
      void vertex(double v1, double v2, double v3);
      /**
       * Set a normal for the next vertex.
       * This also turns off automatic calculation of normals.
       * (This is used if there is lighting in the scene, mostly.)
       * This should be perpendicular to the plane of the object that you're drawing.
       * @param n1 The x value of the normal.
       * @param n2 The y value of the normal.
       * @param n3 The z value of the normal.
       */
      void normal(double n1, double n2, double n3);
      // Makes it so normals are automatically calculated.
      void calculateNormals();
      /**
       * Draws on a vertex array.
       * This is normally used for OpenGL 3 calls and for particle effects.
       * @param verts The vertex array to draw.
       * @param cols The color array to draw from.
       * @param texs The texture array to draw from.
       * @param size The amount of points to draw.
       * @param vertGap Should be 2 if 2D and 3 if 3D.
       * @param colGap Should be 3 if RGB and 4 if ARGB.
       * @param type The type of shapes to draw (GL_LINES, GL_POINTS, GL_TRIANGLES, GL_QUADS)
       */
      void drawArray(float* verts, float* cols, float* texs, int size, int vertGap, int colGap, int type);
      /**
       * Draws on a vertex array.
       * This is normally used for OpenGL 3 calls and for particle effects.
       * @param verts The vertex array to draw.
       * @param cols The color array to draw from.
       * @param texs The texture array to draw from.
       * @param size The amount of points to draw.
       * @param vertGap Should be 2 if 2D and 3 if 3D.
       * @param colGap Should be 3 if RGB and 4 if ARGB.
       * @param type The type of shapes to draw (LINES, POINTS, TRIANGLES, QUADS)
       */
      void drawArray(float* verts, float* cols, float* texs, int size, int vertGap, int colGap, std::string type);
      // Tells OpenGL to stop drawing polygons/lines. (Same as glEnd).
      void end();
      // Get the width of the GLDraw object (The width of the window)
      double getWidth(){return width;};
      // Get the height of the GLDraw object (The height of the window)
      double getHeight(){return height;};
      // Start drawing; Draws the background, clears the buffer, and gets ready to draw.
      void start();
      // Finishes drawing and draws everything to the screen.
      void finish();
      // Finishes drawing and flushes the buffers. (Doesn't draw to the screen.)
      void finishNoDraw();
      // Matrices
      // Push a Translation Matrix onto the OpenGL stack.
      void pushMatrix();
      // Pop a Translation Matrix onto the OpenGL stack.
      void popMatrix();
      /**
       * Translates the world on window coordinates.
       * @param x The amount of pixels to translate right.
       * @param y The amount of pixels to translate down.
       */
      void translateW(double x, double y){translateW(x,y,0);};
      /**
       * Translates the world on window coordinates.
       * @param x The amount of pixels to translate right.
       * @param y The amount of pixels to translate down.
       * @param z The amount to translate on the z axis.
       */
      void translateW(double x, double y, double z){
         translate(x*2/width, -y*2/height, z);
      }
      /**
       * Translates the world on OpenGL coordinates.
       * @param x The amount of coordinates to translate right.
       * @param y The amount of coordinates to translate up.
       */
      void translate(double x, double y){translate(x,y,0);};
      /**
       * Translates the world on OpenGL coordinates.
       * @param x The amount of coordinates to translate right.
       * @param y The amount of coordinates to translate up.
       * @param z The amount of coordinates to translate back.
       */
      void translate(double x, double y, double z);
      /**
       * Scales the world.
       * @param w The scaling factor for the x-axis.
       * @param h The scaling factor for the y-axis.
       */
      void scale(double w, double h){scale(w,h,1);};
      /**
       * Scales the world.
       * @param w The scaling factor for the x-axis.
       * @param h The scaling factor for the y-axis.
       * @param l The scaling factor for the z axis.
       */
      void scale(double w, double h, double l);
      /**
       * Rotates the world counter-clockwise.
       * @param angle The angle in degrees to rotate.
       */
      void rotate(double angle){rotate(angle, 0, 0, 1);};
      void rotate(double angle, double x, double y, double z);

      // The next functions are constant regardless of implementation of the GLUtil classes.

      bool popCameraMem();
      void pushCameraMem(double x, double y, double w, double h);
};

/**
 * The Utility class to deal with OpenGL calls
 * This should abstract OpenGL calls.
 * So we shouldn't have to worry about changing a ton of library calls 
 *    if we decide to use a different library.
 * (In practice, though, only GLUT with OpenGL 2.0 is currently implemented...)
 */
class GLUtil{
   private:
      // Just the version of OpenGL we're using.
      float glVersion;
      // Information that is implementation based.
      void* extraInfo;
   public:
      // This handles controls.
      GLControls* control;
      // This handles shaders.
      GLShaders* shade;
      // This handles actual drawing.
      GLDraw* draw;
      // Creates the GLUtil class
      GLUtil();
      // Gets the time elapsed. (Used for deltaTime)
      double getTime();
      // Call this to get something to redraw the screen.
      void redisplay();
      // Gets the OpenGL version. (Useful for seeing what shaders we can use.)
      float version(){
         return glVersion;
      };
      /**
       * Initializes OpenGL so we can actually use it.
       * @param argc The pointer to argc in main.
       * @param argv The argv character array in main.
       * @param idle The update loop that we want to call.
       * @param display The draw loop that we want to call.
       */
      void initialize(int* argc, char** argv, void (*idle)(), void (*display)());
      /**
       * Resizes the window to be a certain size.
       * @param width The width of the window in pixels.
       * @param height The height of the window in pixels.
       */
      void reshapeWindow(int width, int height);
      /**
       * Sets the title of the window.
       * @param newName The new title of the window.
       */
      void renameWindow(std::string newName);
      /**
       * Sets the resolution of the window.
       * This is the effective size of the window, rather than the actual size.
       * @param width The width of the window in pixels, effectively.
       * @param height The height of the window in pixels, effectively.
       */
      void setResolution(int width, int height);
      /**
       * Starts OpenGL's loops up.
       * Run after initialization.
       */
      void start();
      /**
       * What OpenGL should do after reshaping.
       * This is a blank function in the current implementation.
       */
      static void reshape(int width, int height);
};

#endif