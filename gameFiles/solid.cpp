#include "solid.h"

Solid::Solid(double X, double Y) : Instance(X, Y, 1, 1){
    immovable = true;
    r = 0;
    g = 0;
    b = 0;
    name = "Solid";
}

SemiSolid::SemiSolid(double X, double Y) : Instance(X, Y, 1, 1){
    immovable = true;
    r = 0;
    g = 0;
    b = 0.3;
    name = "Solid";
    semiColl[COLL_LEFT] = false;
    semiColl[COLL_RIGHT] = false;
    semiColl[COLL_BOTTOM] = false;
}
