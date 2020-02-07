#include "level.h"

Level::Level(){
   filePath = "";
   createdShaderboxes = false;
   insts = nullptr;
}

Level::~Level(){
   // Deallocate out shader boxes here.
   for (int i = 0; i < shades.size(); i++){
      delete shades[i];
   }
   shades.clear();
   // Deallocate our level here.
   while (insts != nullptr){
      Instances* del = insts;
      insts = insts->next;
      delete del;
   }
}

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

std::vector<Instance*> Level::makeLevel(std::vector<Instance*> previous){
   return previous;
}

std::vector<ShaderBox*> Level::createShaderBoxes(GLUtil* glu){
   std::vector<ShaderBox*> empty;
   return empty;
}

void Level::moveInstance(Instances* move, Level* otherLev){
   if (move->prev == nullptr){
      // We got the head of our linked list
      insts = move->next;
   } else {
      move->prev->next = move->next;
   }
   // Move this to the beginning of the other linked list.
   move->prev = nullptr;
   move->next = otherLev->insts;
   otherLev->insts = move->next;
}
