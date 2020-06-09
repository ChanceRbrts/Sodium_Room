#ifndef dos_obj_textbox
#define dos_obj_textbox

#include "instance.h"
#include "../utils/fontBook.h"

/**
 * Draws a character of text.
 * The idea of this is if every character is drawn separately, we can do stuff like
 * change the color and fonts of specific characters.
 * More specifically, we could also do some things like shaky text.
 */
class Character : public Instance{
   private:
      /// The texture that corresponds to that character.
      int tex;
      /// TODO: The integer corresponding to how the character should move.
      int mode;
   public:
      /**
       * The character viewing constructor.
       * @param X The x position of the character.
       * @param Y The y position of the character.
       * @param W The width of the character.
       * @param H The height of the character.
       */ 
      Character(double X, double Y, double W, double H, int texture, int textMode);
      /**
       * Set the color of the character.
       * (The color otherwise is assumed to be black.)
       * @param R The red part of the color. (0-1)
       * @param G The green part of the color. (0-1)
       * @param B The blue part of the color. (0-1)
       */
      void setColor(double R, double G, double B);
      /**
       * Updates the text box to display a message.
       * @param deltaTime The time in between this frame and the previous frame.
       * @param keyPressed The array of keys pressed this frame.
       * @param keyHeld The array of the keys that are held down.
       */
      void update(double deltaTime, bool* keyPressed, bool* keyHeld);
      /**
       * Draws the Character.
       * @param gld The GLUtil's draw functions.
       * @param gls The GLUtil's shader functions.
       */
      void draw(GLDraw* gld, GLShaders* gls);
};

/**
 * This is the text box that will go on the HUD.
 */
class TextBox : public Instance{
   private:
      /// The fonts being used in the text box.
      std::vector<std::string> loadedFonts;
      /// The lines that are being rendered through the text box.
      std::vector<std::string> lines;
      /// The current position on the line when creating text.
      int currentLinePos;
      /// The last character visible.
      int currentCharVisible;
      /// The current line being rendered.
      int line;
      /// The font currently being used.
      std::string font;
      /// The line that will eventually be rendered.
      std::string finishedLine;
      /// The list of characters that's currently being rendered.
      std::vector<Character *> currentLine;
      /// How long until the next character render.
      double timer;
      /// The max amount of time in animation for character rendering.
      double maxTimer;
      /// Where to start writign text.
      double startXOffset;
      /**
       * A function to analyze commands used.
       * @param comm The command to analyze
       */
      void analyzeCommands(std::string comm);
      /**
       * Splits apart special commands.
       * @param command The command to run.
       */
      void texBoxCommands(std::string command);
      /// A function to create new character to eventually render.
      void createCharacters();
   public:
      /**
       * TODO: Constructor for the text box.
       * @param filename The file to read lines from on the text box.
       */
      TextBox(std::string filename);
      /**
       * Constructor for the text box.
       * @param lines The lines to read on the text box.
       */
      TextBox(std::vector<std::string> textLines);
      /// Deconstructor for the textbox.
      ~TextBox();
      /**
       * Updates the text box to display a message.
       * @param deltaTime The time in between this frame and the previous frame.
       * @param keyPressed The array of keys pressed this frame.
       * @param keyHeld The array of the keys that are held down.
       */
      void update(double deltaTime, bool* keyPressed, bool* keyHeld);
      /**
       * Draws the Text Box.
       * @param gld The GLUtil's draw functions.
       * @param gls The GLUtil's shader functions.
       */
      void draw(GLDraw* gld, GLShaders* gls);
};

#endif