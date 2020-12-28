#include "map.h"

std::map<double, Gap> Map::horizontalMapGap = emptyMap();
std::map<double, Gap> Map::verticalMapGap = emptyMap();

Map::Map(int sID){
   x = 0;
   y = 0;
   w = 0;
   h = 0;
   prevCX = 0;
   prevCY = 0;
   superMapID = sID;
   firstLoad = true;
}

std::map<double, Gap> Map::emptyMap(){
   std::map<double, Gap> ret;
   return ret;
}

std::vector<Level *> Map::getUnloadedLevelsInArea(double X, double Y, double W, double H){
   std::vector<Level *> levs;
   // Change to level coordinates by removing gaps.
   double rX = translateMapCoord(X, true, true);
   double rY = translateMapCoord(Y, false, true);
   double rX2 = translateMapCoord(X+W, true, true);
   double rY2 = translateMapCoord(Y+H, false, true);
   for (int i = 0; i < levels.size(); i++){
      Level* l = levels[i];
      double lX = l->getMXOff();
      double lY = l->getMYOff();
      double lW = l->w;
      double lH = l->h;
      if (rX <= lX+lW && rX2 >= lX && rY <= lY+lH && rY2 >= lY){
         if (!l->getLoaded()){
            // Add gaps before moving the level into the world.
            double trueX = translateMapCoord(lX, true, false);
            double trueY = translateMapCoord(lY, false, false);
            l->moveRoom(trueX, trueY, false);
            // Now, see if a bisection needs to happen.
            std::map<double, Gap>::iterator it = horizontalMapGap.begin();
            // Check for a horizontal bisection.
            for (; it != horizontalMapGap.end(); it++){
               if (it->first > lX+lW) break;
               if (it->first >= lX && it->first <= lX+lW){
                  // Translate the bisection to world coords.
                  l->startBisect(true, it->first-lX+trueX, it->second.length);
               }
            }
            it = verticalMapGap.begin();
            // Check for a vertical bisection.
            for (; it != verticalMapGap.end(); it++){
               if (it->first > lY+lH) break;
               if (it->first >= lY && it->first <= lY+lH){
                  // Translate the bisection to world coords.
                  l->startBisect(false, it->first-lY+trueY, it->second.length);
               }
            }
            levs.push_back(l);
         }
      }
   }
   return levs;  
}

void Map::addLevel(Level* l, double X, double Y){
   l->moveInMap(X*32, Y*32, false);
   l->moveRoom(X*32, Y*32, false);
   l->setWidthHeight();
   // pointInt area = (pointInt){(int)(X/100), (int)(Y/100), 0};
   if (levels.size() == 0){
      x = l->getMXOff();
      y = l->getMYOff();
      w = l->w;
      h = l->h;
   } else{
      float levX = l->getMXOff();
      float levY = l->getMYOff();
      float levW = l->w;
      float levH = l->h;
      // Modify the leftmost bounds first, since they could affect w and h.
      if (levX < x){
         float dX = x-levX;
         w += dX;
         x = levX;
      }
      if (levY < y){
         float dY = y-levY;
         h += dY;
         y = levY;
      }
      // Now, affect the rightmost bounds, since they can't affect x or y.
      if (levX+levW-x > w) w = levX+levW-x;
      if (levY+levH-y > h) h = levY+levH-y;
   }
   levels.push_back(l);
}

bool Map::inBounds(double X, double Y, double W, double H){
   double mX = x;
   double mY = y;
   double mX2 = x+w;
   double mY2 = y+h;
   // Adjust the bounds of the map according to the amount of gaps in the level.
   std::map<double, Gap>::iterator it = horizontalMapGap.begin();
   // Alter the horizontal bounds first.
   for (; it != horizontalMapGap.end(); it++){
      if (it->first <= x) mX += it->second.length;
      if (it->first <= x+w) mX2 += it->second.length;
      else break;
   }
   // Alter the vertical bounds.
   it = verticalMapGap.begin();
   for (; it != verticalMapGap.end(); it++){
      if (it->first <= y) mY += it->second.length;
      if (it->first <= y+w) mY2 += it->second.length;
      else break;
   }
   return mX <= X+W && mX2 >= X && mY <= Y+H && mY2 >= Y;
}

double Map::translateMapCoord(double prevCoord, bool horizontal, bool reverse){
   std::map<double, Gap>* toUse = horizontal ? &horizontalMapGap : &verticalMapGap;
   std::map<double, Gap>::iterator it = toUse->begin();
   double coord = prevCoord;
   if (reverse){
      // Get rid of all of the gaps.
      double gapLength = 0;
      for (; it != toUse->end(); it++){
         // If the point is before the gap, then break here.
         if (prevCoord-gapLength < it->first){
            coord -= gapLength;
            break;
         }
         gapLength += it->second.length;
         // If removing the gap puts the x position before the gap, then it's directly on the gap.
         if (prevCoord-gapLength < it->first) return it->first;
      }
   } else {
      // Just add to the coordinate! 
      for (; it != toUse->end(); it++){
         // Check to see if the map coordinate is still after 
         // where the gap would be in map coordinates.
         if (it->first >= prevCoord) break;
         coord += it->second.length;
      }
   }
   return coord;
}

std::vector<Level *> Map::updateLoadedLevels(GLUtil* glu){
   double newX = glu->draw->camX;
   double newY = glu->draw->camY;
   double wid = glu->draw->getWidth();
   double hei = glu->draw->getHeight();
   return updateLoadedLevels(newX, newY, wid, hei);
}

std::vector<Level *> Map::updateLoadedLevels(double X, double Y, double W, double H){
   std::vector<Level *> levs;
   // Get the real x and y values by taking away the gaps.
   double rX = translateMapCoord(X, true, true);
   double rY = translateMapCoord(Y, false, true);
   // Check to see where we need to load a level.
   bool stillCamera = int(rX/32) == int(prevCX/32);
   stillCamera = stillCamera && int (rY/32) == int(prevCY/32);
   // Set the new camera posiiton.
   prevCX = rX;
   prevCY = rY;
   // If there's no place to check for a new level, just return.
   if (stillCamera && !firstLoad) return levs;
   levs = getUnloadedLevelsInArea(X-W*3/4, Y-H*3/4, W*5/2, H*5/2);
   firstLoad = false;
   return levs;
}

void Map::addGap(double P, double W, bool horiz, double minPoint, double maxPoint, bool relative){
   std::map<double, Gap>* toUse = horiz ? &horizontalMapGap : &verticalMapGap;
   std::map<double, Gap>::iterator gaps = toUse->begin();
   // This is so broken that no gap gets added. (Whoops) Fix this.
   bool inMap = false;
   for (; gaps != toUse->end(); gaps++){
      double toCompare = gaps->first;
      if (abs(toCompare-P) < 0.001){
         inMap = true;
         Gap g = (*toUse)[toCompare];
         (*toUse)[toCompare] = (Gap){W+(relative?gaps->second.length:0), g.minP, g.maxP};
         // Remove the gap if it's less than or equal to 0.
         if ((*toUse)[toCompare].length < 0.001) toUse->erase(toCompare);
         break;
      } else if (toCompare > P && W != 0){
         // Don't search the rest of the map; it's useless.
         break;
      }
   }
   if (!inMap){
      // Don't add the gap if the gap is 0.
      if (W == 0) return;
      // Insert the gap in the map if it's not there.
      toUse->insert(std::pair<double, Gap>(P, (Gap){W, minPoint, maxPoint}));
   }
}

void Map::collideGapWithInstance(Instance* o, double deltaTime, bool horiz){
   // Use w to go with p, h to go with q.
   double* oP = &(o->x);
   double oW = o->w;
   double* oDP = &(o->dX);
   double* oQ = &(o->y);
   double oH = o->h;
   double* oDQ = &(o->dY);
   // If not horizontal, flip everything!
   // I have it like this to avoid 6 if statements in a row with tertiary statements.
   if (!horiz){
      oP = &(o->y);
      oW = o->h;
      oDP = &(o->dY);
      oQ = &(o->x);
      oH = o->w;
      oDQ = &(o->dX);
   }
   std::map<double, Gap>* toUse = horiz ? &horizontalMapGap : &verticalMapGap;
   std::map<double, Gap>::iterator gaps = toUse->begin(); 
   for (; gaps != toUse->end(); gaps++){
      // Make sure the gaps are real gaps and not just floating point errors.
      if (gaps->second.length < 1){
         continue;
      }
      double p = translateMapCoord(gaps->first, horiz, true);
      double w = gaps->second.length;
      double minY = translateMapCoord(gaps->second.minP, !horiz, false);
      double maxY = translateMapCoord(gaps->second.maxP, !horiz, false);
      // Do collision for the gaps.
      for (int i = 0; i < 2; i++){
         // Using i as a corner check.
         // Check the left wall.
         if (*oP+oW <= p && *oP+oW+*oDP*deltaTime > p && 
             (*oQ+*oDQ*deltaTime*i < minY || *oQ+oH+*oDQ*deltaTime*i > maxY)){
            *oDP = 0;
            *oP = p-oW;
         }
         // Check the right wall.
         if (*oP >= p+w && *oP+*oDP*deltaTime < p+w && 
             (*oQ+*oDQ*deltaTime*i < minY || *oQ+oH+*oDQ*deltaTime*i > maxY)){
            *oDP = 0;
            *oP = p+w;
         }
         // Check the top wall.
         if (*oQ >= minY && *oQ+*oDQ*deltaTime < minY && 
             *oP+oW+*oDP*deltaTime*i > p && *oP+*oDP*deltaTime*i < p+w){
            *oDQ = 0;
            *oQ = minY;
         }
         // Check the bottom wall.
         if (*oQ+oH <= maxY && *oQ+oH+*oDQ*deltaTime > maxY && 
             *oP+oW+*oDP*deltaTime*i > p && *oP+*oDP*deltaTime*i < p+w){
            *oDQ = 0;
            *oQ = maxY-oH;
            o->ground();
         }
      }
   }
}

void Map::drawGaps(GLUtil* glu){
   GLDraw* gld = glu->draw;
   GLShaders* gls = glu->shade;
   // Add the gap shader in if it's not in already.
   if (!gls->programExists("gap")){
      gls->createProgram("", "gameFiles/shaders/gap", "gap");
   }
   double camX = gld->camX;
   double camY = gld->camY;
   double camW = gld->getWidth();
   double camH = gld->getHeight();
   std::map<double, Gap>::iterator gaps = horizontalMapGap.begin();
   int program = gls->bindShader("gap");
   // Add uniforms for the camera here.
   gls->addUniform(program, "camX", camX);
   gls->addUniform(program, "camY", camY);
   // This could probably be cut down into a shorter function...
   // Draw horizontal map gaps.
   for (; gaps != horizontalMapGap.end(); gaps++){
      // Figure out where the gap is and what y values the gaps go for.
      double gapX = translateMapCoord(gaps->first, true, false);
      if (gapX > camX+camW) break;
      else if (gapX+gaps->second.length < camX) continue;
      double minY = translateMapCoord(gaps->second.minP, false, false);
      double maxY = translateMapCoord(gaps->second.maxP, false, false);
      double gapW = gaps->second.length;
      // Draw the gaps!
      gld->begin("QUADS");
      // Draw a gap at the top
      if (minY > camY){
         gld->vertW(std::max(camX, gapX), camY);
         gld->vertW(std::max(camX, gapX), minY);
         gld->vertW(std::min(camX+camW, gapX+gapW), minY);
         gld->vertW(std::min(camX+camW, gapX+gapW), camY);
      }
      // Draw a gap at the bottom.
      if (maxY < camY+camH){
         gld->vertW(std::max(camX, gapX), maxY);
         gld->vertW(std::max(camX, gapX), camY+camH);
         gld->vertW(std::min(camX+camW, gapX+gapW), camY+camH);
         gld->vertW(std::min(camX+camW, gapX+gapW), maxY);
      }
      gld->end();
   }
   // Draw vertical map gaps.
   gaps = verticalMapGap.begin();
   for (; gaps != verticalMapGap.end(); gaps++){
      // Figure out where the gap is and what x values the gaps go for.
      double gapY = translateMapCoord(gaps->first, false, false);
      if (gapY > camY+camH) break;
      else if (gapY+gaps->second.length < camY) continue;
      double minX = translateMapCoord(gaps->second.minP, true, false);
      double maxX = translateMapCoord(gaps->second.maxP, true, false);
      double gapH = gaps->second.length;
      // Draw the gaps!
      gld->begin("QUADS");
      // Draw a gap to the left.
      if (minX > camX){
         gld->vertW(camX, std::max(camY, gapY));
         gld->vertW(camX, std::min(camY+camH, gapY+gapH));
         gld->vertW(minX, std::min(camY+camH, gapY+gapH));
         gld->vertW(minX, std::max(camY, gapY));
      }
      // Draw a gap to the right.
      if (maxX < camX+camW){
         gld->vertW(maxX, std::max(camY, gapY));
         gld->vertW(maxX, std::min(camY+camH, gapY+gapH));
         gld->vertW(camX+camW, std::min(camY+camH, gapY+gapH));
         gld->vertW(camX+camW, std::max(camY, gapY));
      }
      gld->end();
   }
   gls->unbindShader();
}
