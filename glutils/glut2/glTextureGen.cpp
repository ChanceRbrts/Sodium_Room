#include "../glUtil.h"
#include "glut.h"

GLTextureGen::GLTextureGen(void* eInfo){
   extraInfo = eInfo;
}

unsigned int GLTextureGen::loadImage(std::string img){
   unsigned int tex;
   // TODO.
   return tex;
}

pointInt GLTextureGen::renderString(std::string str, std::string font, float r, float g, float b){
   // TODO.
   return (pointInt){0,0,0};
}

std::string GLTextureGen::fontPath(std::string font){
   std::vector<std::string> fPath;
   #ifdef __APPLE__
   // I know that OSX has three places where fonts can be found.
   fPath.push_back("/Library/Fonts");
   fPath.push_back("/System/Library/Fonts");
   fPath.push_back("~/Library/Fonts");
   #else
   // I'm not entirely sure about the other operating systems, though...
   #ifdef __linux__
   fPath.push_back("/usr/share/fonts");
   fPath.push_back("/usr/share/fonts/truetype");
   #else
   fPath.push_back("C:/Windows/Fonts");
   #endif
   #endif
   // Check all possible font locations.
   for (int i = 0; i < fPath.size(); i++){
      std::string filePath = fPath[i]+"/"+font;
      // Check if the font is in the expected location.
      FILE* test = fopen(filePath.c_str(), "r");
      if (test != nullptr){
         fclose(test);
         return filePath;
      }
      fclose(test);
   }
   return font;
}