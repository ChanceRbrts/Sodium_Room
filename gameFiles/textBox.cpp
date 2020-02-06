#include "textBox.h"

TextBox::TextBox(std::string filename) : Instance(0, 0, 0, 0){
   /*FILE* f = fopen(filename.c_str(), "r");
   if (f == nullptr){
      fprintf(stderr, "Error: File %s does not exist.", filename.c_str());
   }
   while (!feof){
      
   }*/
}

TextBox::TextBox(std::vector<std::string> textLines) : Instance(0, 0, 0, 0){
   lines = textLines;
   currentLinePos = 0;
   line = 0;
   finishedLine = "";
   maxTimer = 0.03;
   timer = maxTimer;
   startXOffset = 0;
   currentCharVisible = 0;
   r = 0;
   g = 0;
   b = 0;
   font = "Courier New";
}

TextBox::~TextBox(){
   // Remove all fonts that we added in to save space.
   for (int i = 0; i < loadedFonts.size(); i++){
      FontBook::unloadFont(loadedFonts[i]);
   }
   loadedFonts.clear();
}

void TextBox::analyzeCommands(std::string comm){
   if (comm.length() > 5 && comm.substr(0, 5).compare("font:") == 0){
      std::string newFont = comm.substr(5);
      FontBook::loadFont(newFont);
      font = newFont;
   } else if (comm.length() > 6 && comm.substr(0,6).compare("color:") == 0){
      std::string newColor = comm.substr(6);
      if (newColor.length() != 6){
         return;
      }
      int val = strtol(newColor.c_str(), 0, 16);
      r = (val>>16&255)*1.0/255.0;
      g = (val>>8&255)*1.0/255.0;
      b = (val&255)*1.0/255.0;
   }
}

void TextBox::texBoxCommands(std::string command){
   command += "\n";
   std::string comm = "";
   for (int i = 0; i < command.length(); i++){
      char c = command[i];
      if (c == '|' || i == command.length()-1){
         // Analyze the command. (Probably would be better with regex?)
         analyzeCommands(comm);
         comm = "";
      } else {
         comm += c;
      }
   }

}

void TextBox::createCharacters(){
   // I'm attempting to group letters by words here.
   // Words in this case will be broken by a space or a hyphen.
   //double tH = 4.0/15.0*h;
   double tH = 7.0/30.0*h;
   double wEnd = 63.0/64.0;
   double wLen = 62.0/64.0;
   double wStart = w/64.0;
   double wordLength = 0.0;
   double xOffset = 0;
   double yOffset = 0;
   std::vector<double> charLength;
   std::vector<int> charTexs;
   std::vector<std::string> commands;
   std::vector<int> addOffset;
   bool keepGoing = true;
   int futureLinePos = currentLinePos;
   bool writeWord = false;
   std::string prevFont = font;
   double prevR = r;
   double prevG = g;
   double prevB = b;
   while (keepGoing){
      char c = finishedLine[futureLinePos];
      pointInt v1 = FontBook::getCharacter(font, c);
      // Add the character
      if (c != ' ' && c != '-' && c != '|'){
         // Assume no command was made here.
         if (commands.size() == charTexs.size()){
            commands.push_back("");
            addOffset.push_back(0);
         }
         charTexs.push_back(v1.z);
         double len = tH*(double)(v1.x)/(1.0*v1.y);
         wordLength += len;
         charLength.push_back(len);
      } else if (c == '|'){
         // A command was made.
         // The offset will be the length of the string we make.
         // Make string with two |s.
         std::string command = "";
         bool makeCommand = true;
         while (makeCommand){
            futureLinePos += 1;
            char v = finishedLine[futureLinePos];
            if (v == '|') makeCommand = false;
            else command += v;
         }
         texBoxCommands(command);
         // Add the command to the next character.
         if (commands.size() == charTexs.size()){
            commands.push_back(command);
            addOffset.push_back(command.length()+2);
         } else {
            // If there's already a command here, let's add to it.
            commands[commands.size()-1] += "|"+command;
            addOffset[commands.size()-1] += command.length()+2;
         }
      } else{ 
         writeWord = true;
      }
      // Check to see if we need to write to our line.
      if (futureLinePos == finishedLine.length()-1){
         writeWord = true;
         keepGoing = false;
      }
      if (wordLength > w*wLen){
         writeWord = true;
      }
      if (writeWord){
         // Reset the font and colors in case the word doesn't get drawn.
         font = prevFont;
         r = prevR;
         g = prevG;
         b = prevB;
         int linePosOffset = 0;
         // Check if the word will go out of bounds.
         if (wordLength+xOffset+wStart > w*wEnd && wordLength < w*wLen){
            xOffset = 0;
            yOffset += tH*4/5; // (6/60ths to get stuff aligned properly.)
         }
         if (yOffset+tH > h){
            // DO NOT DRAW ANY CHARACTERS; JUST RETURN AND WAIT UNTIL THEY HIT ENTER AGAIN.
            keepGoing = false;
         } else {
            int i = 0;
            bool addSpace = true;
            // Doing a while loop here so we have a reference of i after we use it.
            while (i < charLength.size()){
               // Make sure a command has been run.
               texBoxCommands(commands[i]);
               double y = yOffset + h/24.0;
               double x = xOffset + wStart;
               // If the character is out of bounds, we don't want to draw it.
               if (x+charLength[i] > w*wEnd){
                  addSpace = false;
                  break;
               }
               // Create the character.
               Character* textCha = new Character(x,y,charLength[i],tH,charTexs[i],0);
               textCha->setColor(r, g, b);
               currentLine.push_back(textCha);
               xOffset += charLength[i];
               i++;
               // Up the offset.
               linePosOffset += addOffset[i];
            }
            // If we can, let's add a space or hyphen character.
            if (addSpace){ 
               linePosOffset += 1;
               if (commands.size() > charTexs.size()){
                  texBoxCommands(commands[commands.size()-1]);
                  linePosOffset += addOffset[commands.size()-1];
               }
            }
            if (xOffset+tH*(double)(v1.x)/(1.0*v1.y) < w*wLen){
               double wid = tH*(double)(v1.x)/(1.0*v1.y);
               xOffset += wid;
               currentLine.push_back(new Character(x,y,wid,tH,v1.z,0));
            }
            currentLinePos += i+linePosOffset;
            // If we have more text to draw, then let's keep that in.
            if (i < charLength.size()){
               charTexs.erase(charTexs.begin(), charTexs.begin()+i);
               charLength.erase(charLength.begin(), charLength.begin()+i);
               commands.erase(commands.begin(), commands.begin()+i);
               addOffset.erase(addOffset.begin(), addOffset.begin()+1);
            } else{
               charTexs.clear();
               charLength.clear();
               commands.clear();
               addOffset.clear();
            } 
            // Finally, let's update the word length again.
            wordLength = 0;
            for (int i = 0; i < charLength.size(); i++){
               wordLength += charLength[i];
            }
         }
         writeWord = false;
         // Update the prev stuff.
         prevFont = font;
         prevR = r;
         prevG = g;
         prevB = b;
      }
      futureLinePos += 1;
   }
}

void TextBox::update(double deltaTime, bool* keyPressed, bool* keyHeld){
   if (h == 0) return;
   if (finishedLine.length() == 0){
      if (line >= lines.size()){
         remove = true;
         return;
      }
      finishedLine = lines[line];
      currentLinePos = 0;
      createCharacters();
      line += 1;
   }
   // Add the line throughout time.
   if (currentCharVisible < currentLine.size()){
      timer -= deltaTime;
      if (timer < 0){
         timer += maxTimer;
         currentCharVisible += 1;
      }
      if (keyPressed[BUTTON_A]){
         // Make everything visible.
         currentCharVisible = currentLine.size();
      }
   } else {
      if (keyPressed[BUTTON_A]){
         currentCharVisible = 0;
         // De-allocate the characters and clear the buffer.
         for (int i = 0; i < currentLine.size(); i++){
            delete currentLine[i];
         }
         currentLine.clear();
         if (currentLinePos < finishedLine.length()){
            createCharacters();
         } else {
            finishedLine = "";
         }
      }
   }
}

void TextBox::draw(GLDraw* gld, GLShaders* gls){
   double sW = 4;
   w = gld->getWidth();
   h = gld->getHeight()/4;
   // This assumes that the Text Box is in the HUD.
   // Draw the actual box.
   gld->color(1, 1, 1, 0.75);
   gld->begin("QUADS");
   gld->vertW(sW, sW);
   gld->vertW(sW, h-sW);
   gld->vertW(w-sW, h-sW);
   gld->vertW(w-sW, sW);
   gld->end();
   // Draw the Outline
   gld->color(0, 0, 0, 1);
   gld->begin("QUADS");
   gld->vertW(0, 0);
   gld->vertW(0, 0+h);
   gld->vertW(sW, 0+h);
   gld->vertW(sW, 0);
   gld->vertW(0, 0);
   gld->vertW(0, sW);
   gld->vertW(w, sW);
   gld->vertW(w, 0);
   gld->vertW(w-sW, 0);
   gld->vertW(w-sW, 0+h);
   gld->vertW(w, 0+h);
   gld->vertW(w, 0);
   gld->vertW(0, h-sW);
   gld->vertW(0, h);
   gld->vertW(w, h);
   gld->vertW(w, h-sW);
   gld->end();
   // Draw the characters.
   for (int i = 0; i < currentLine.size() && i < currentCharVisible; i++){
      currentLine[i]->draw(gld, gls);
   }
}

Character::Character(double X, double Y, double W, double H, int texture, int textMode) 
      : Instance(X/32,Y/32,W/32,H/32){
   tex = texture;
   mode = textMode;
   r = 0;
   g = 0;
   b = 0;
}

void Character::setColor(double R, double G, double B){
   r = R;
   g = G;
   b = B;
}

void Character::update(double deltaTime, bool* keyPressed, bool* keyHeld){
   if (mode == 1){

   }
}

void Character::draw(GLDraw* gld, GLShaders* gls){
   if (x == 0 && y == 0) return;
   gld->color(r, g, b, 1);
   gld->enableTextures();
   gld->bindTexture(tex);
   gld->begin("QUADS");
   gld->texCoords(0, 0);
   gld->vertW(x, y);
   gld->texCoords(0, 1);
   gld->vertW(x, y+h);
   gld->texCoords(1, 1);
   gld->vertW(x+w, y+h);
   gld->texCoords(1, 0);
   gld->vertW(x+w, y);
   gld->end();
   gld->bindTexture(0);
   gld->disableTextures();
}
