#ifndef dos_fontbook
#define dos_fontbook

#include "../glutils/glUtil.h"
#include <map>

/**
 * Static Singleton Class to Deal with Classes and Textures.
 * The purpose of this is to have a database for textures for each letter of the alphabet.
 * This is useful due to the fact that OpenGL textures will coordinate to different fonts.
 */
class FontBook{
   private:
      static std::map<std::string, std::map<char, pointInt>> fontBook;
      static GLTextureGen* glt;
   public:
      // Something to just create an empty map.
      static std::map<std::string, std::map<char, pointInt>> emptyMap();
      static void initialize(GLUtil* glu);
      /**
       * Puts a font into the font book.
       * @param font The font to put in the font book.
       * @return Whether the font has loaded.
       */
      static bool loadFont(std::string font);
      /**
       * Removes all the textures of the font from the book.
       * @param font The font to remove from the font book.
       */
      static void unloadFont(std::string font);
      /**
       * Gets a texture for a character for a font.
       * @param font The font of the texture.
       * @param value The character to do the font with.
       */
      static pointInt getCharacter(std::string font, char value);
      /**
       * Remove all fonts.
       */
      static void destroy();
};

#endif