#include "texBook.h"

GLTextureGen* TexBook::glt = nullptr;
std::map<std::string, unsigned int> TexBook::texBook = TexBook::emptyMap();

std::map<std::string, unsigned int> TexBook::emptyMap(){
   std::map<std::string, unsigned int> m;
   return m;
}

void TexBook::initialize(GLUtil* glu){
    glt = glu->draw->texGen;
}

bool TexBook::hasTexture(std::string tex){
    std::map<std::string, unsigned int>::iterator it = texBook.find(tex);
    return it != texBook.end();
}

int TexBook::loadTexture(std::string tex){
    if (glt == nullptr){
        fprintf(stderr, "Error: The Fontbook isn't initialized.");
        return -1;
    }
    unsigned int t = glt->loadImage(tex);
    if (t == -1) return -1;
    texBook.insert({tex, t});
    return t;
}

void TexBook::unloadTexture(std::string tex){
    if (hasTexture(tex)){
        int i = texBook.at(tex);
        glt->removeTexture(i);
        texBook.erase(tex);
    }
}

int TexBook::getTexture(std::string tex){
    if (!hasTexture(tex)) return -1;
    return texBook.at(tex);
}
