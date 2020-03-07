#ifndef dos_texbook
#define dos_texbook

#include "../glutils/glUtil.h"
#include <map>

/**
 * Static Singleton Class to Deal with Classes and Textures.
 * The purpose of this is to have a database for textures.
 * This is useful so we don't have multiple textures of the same file loaded.
 */
class TexBook{
    private:
        static std::map<std::string, unsigned int> texBook;
        static GLTextureGen* glt;
    public:
        // Something to just create an empty map.
        static std::map<std::string, unsigned int> emptyMap();
        static void initialize(GLUtil* glu);
        /**
         * Puts a texture into the texture book.
         * @param tex The texture to put in the texture book.
         * @return The texture ID. (-1 if texture wasn't created properly.)
         */
        static int loadTexture(std::string tex);
        /**
         * See if we have the texture we need.
         * @param tex The texture that we're searching for.
         * @return Whether or not the texture is in the texture book.
         */
        static bool hasTexture(std::string tex);
        /**
         * Removes a texture from the book.
         * @param tex The texture to remove from the texture book.
         */
        static void unloadTexture(std::string tex);
        /**
         * Gets a texture;
         * @param tex The texture to get.
         */
        static int getTexture(std::string tex);
        /**
         * Remove all textures.
         */
        static void destroy();
};

#endif