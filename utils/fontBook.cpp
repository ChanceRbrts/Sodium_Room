#include "fontBook.h"

GLTextureGen* FontBook::glt = nullptr;
std::map<std::string, std::map<char, pointInt>> FontBook::fontBook = emptyMap();

std::map<std::string, std::map<char, pointInt>> FontBook::emptyMap(){
   std::map<std::string, std::map<char, pointInt>> m;
   return m;
}

void FontBook::initialize(GLUtil* glu){
   glt = glu->draw->texGen;
}

bool FontBook::loadFont(std::string font){
   if (glt == nullptr){
      fprintf(stderr, "Error: The Fontbook isn't initialized.");
      return false;
   }
   std::map<char, pointInt> fontTex;
   // Go through all readable characters and create a texture for that font.
   for (int i = 32; i < 127; i++){
      char c = (char)i;
      std::string s = std::string("")+c;
      pointInt texMap = glt->renderString(s, font, 1, 1, 1);
      if (texMap.z == -1) return false;
      fontTex.insert({c, texMap});
   }
   fontBook.insert({font, fontTex});
   return true;
}

void FontBook::unloadFont(std::string font){
   std::map<char, pointInt> fontTex = fontBook.at(font);
   std::map<char, pointInt>::iterator iB = fontTex.begin();
   while (iB != fontTex.end()){
      glt->removeTexture(iB->second.z);
      iB++;
   }
   fontTex.clear();
}

pointInt FontBook::getCharacter(std::string font, char value){
   pointInt tex = fontBook.at(font).at(value);
   return tex;
}

void FontBook::destroy(){
   std::map<std::string, std::map<char, pointInt>>::iterator i = fontBook.begin();
   while (i != fontBook.end()){
      FontBook::unloadFont(i->first);
      i++;
   }
   fontBook.clear();
}
