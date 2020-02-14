#include "solid.h"

Solid::Solid(double X, double Y) : Instance(X, Y, 1, 1){
    immovable = true;
    r = 0;
    g = 0;
    b = 0;
    name = "Solid";
}
