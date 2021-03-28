#include "solid.h"

Solid::Solid(double X, double Y) : Solid(X, Y, 15){}

Solid::Solid(double X, double Y, int semiCollRep) : Instance(X, Y, 1, 1){
    immovable = true;
    semiColl[COLL_TOP] = semiCollRep&1;
    semiColl[COLL_BOTTOM] = (semiCollRep>>1)&1;
    semiColl[COLL_LEFT] = (semiCollRep>>2)&1;
    semiColl[COLL_RIGHT] = (semiCollRep>>3)&1;
    r = 0.15*(2-semiColl[COLL_LEFT]-semiColl[COLL_RIGHT]);
    g = 0.3*(1-semiColl[COLL_TOP]);
    b = 0.3*(1-semiColl[COLL_BOTTOM]);
    name = "Solid";
    noArcCol = true;
}

/*
SemiSolid::SemiSolid(double X, double Y) : Instance(X, Y, 1, 1){
    immovable = true;
    r = 0;
    g = 0;
    b = 0.3;
    name = "Solid";
    semiColl[COLL_LEFT] = false;
    semiColl[COLL_RIGHT] = false;
    semiColl[COLL_BOTTOM] = false;
}*/
