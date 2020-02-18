#include "../glUtil.h"
#include "sdl.h"

GLTextureGen::GLTextureGen(void* eInfo){
   extraInfo = eInfo;
}

unsigned int GLTextureGen::loadImage(std::string img){
   unsigned int tex;
   SDL_Surface *image = IMG_Load(img.c_str());
   if (!image){
      fprintf(stderr, "ERROR: %s doesn't exist.\n", img.c_str());
      return -1;
   }
   glGenTextures(1, &tex);
   glBindTexture(GL_TEXTURE_2D, tex);
   int bpp = image->format->BytesPerPixel;
   // int mod = bpp == 4 ? GL_RGBA : GL_RGB;
   int mod = bpp == 4 ? GL_RGBA : GL_RGB;
   glTexImage2D(GL_TEXTURE_2D, 0, mod, image->w, image->h, 0, mod, GL_UNSIGNED_BYTE, image->pixels);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   // We want to keep the surface so we actually have data being pointed to.
   SDL_FreeSurface(image);
   return tex;
}

pointInt GLTextureGen::renderString(std::string str, std::string font, float r, float g, float b){
   // Enable Tex2D and Blending
   bool glTextureEn = glIsEnabled(GL_TEXTURE_2D);
   bool glBlendEn = glIsEnabled(GL_BLEND);
   if (!glTextureEn) glEnable(GL_TEXTURE_2D);
   if (!glBlendEn){
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }
   // The font could be in a separate directory, so we need to make sure to check different directories for fonts.
   std::string f = fontPath(font);
   TTF_Font* fnt = TTF_OpenFont(f.c_str(), 64);
   int tex;
   if (fnt == nullptr){
      fprintf(stderr, "ERROR: Cannot render font %s\n", font.c_str());
      return (pointInt){-1, -1, 0};
   }
   Uint8 R = (Uint8)(r*255);
   Uint8 G = (Uint8)(g*255);
   Uint8 B = (Uint8)(b*255);
   SDL_Surface* image = TTF_RenderText_Blended(fnt, str.c_str(), {R,G,B});
   glGenTextures(1, (unsigned int *)&tex);
   glBindTexture(GL_TEXTURE_2D, tex);
   int w = image->w;
   int h = image->h;
   int bpp = image->format->BytesPerPixel;
   int mod = bpp == 4 ? GL_RGBA : GL_RGB;
   //printf("%x\n", image->format->Amask);
   glTexImage2D(GL_TEXTURE_2D, 0, mod, w, h, 0, mod, GL_UNSIGNED_BYTE, image->pixels);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glBindTexture(GL_TEXTURE_2D, 0);
   if (!glTextureEn) glDisable(GL_TEXTURE_2D);
   if (!glBlendEn) glDisable(GL_BLEND);
   // We want to keep the surface so we actually have data being pointed to.
   SDL_FreeSurface(image);
   TTF_CloseFont(fnt);
   return (pointInt){w,h,tex};
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
      std::string filePath = fPath[i]+"/"+font+".ttf";
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

void GLTextureGen::removeTexture(int tex){
   glDeleteTextures(1, (unsigned int *)&tex);
}
