#include "level.h"

/**
 * Build a level from a file directory.
 */
std::vector<Instance*> Level::createLevel(){
   std::vector<Instance*> instances;
   if (filePath.length() > 0){
      FILE* f = fopen((std::string("gameFiles/levels/levelData/")+filePath+".txt").c_str(), "r");
      if (f == nullptr){
         fprintf(stderr, "ERROR: %s doesn't exist.\n", (filePath+".txt").c_str());
         return makeLevel(instances);
      } 
      std::string line = "";
      int mode = DEFAULT;
      int yVal = 0;
      int wid = 0;
      while (!feof(f)){
         char c = fgetc(f);
         if (c == '\n' || feof(f)){
            if (mode == TEXTURES){
               // Look for textures layout. (TODO)
            } else if (mode == LAYOUT){
               // Look for the layout of the build.
               for (int i = 0; i < line.length(); i++){
                  if (line[i] != ' '){
                     // TODO: Add textures to this solid object?
                     instances.push_back(new Solid(i,yVal));
                  }
               }
               if (line.length() > wid) wid = line.length();
               yVal += 1;
            }
            if (line.find("Textures") != std::string::npos){
               mode = TEXTURES;
            } else if (line.find("Layout") != std::string::npos){
               mode = LAYOUT;
            }
            line = "";
         } else {
            line += c;
         }
      }
      w = wid;
      h = yVal;
   }
   return makeLevel(instances);
}

/**
 * This function returns all of the objects in the room.
 */
std::vector<Instance*> Level::makeLevel(std::vector<Instance*> previous){
   return previous;
}

/**
 * This functions returns all of the shader boxes that are in the room.
 */
std::vector<ShaderBox*> Level::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox*> empty;
   return empty;
}