#include "grate.h"

Grate::Grate(double X, double Y, double W) : Instance(X, Y, W, 1){
   immovable = true;
   r = 0.7;
   g = 0.7;
   b = 0.7;
   name = "Grate";
}