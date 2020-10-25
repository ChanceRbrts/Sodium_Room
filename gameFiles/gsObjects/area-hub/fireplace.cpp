#include "fireplace.h"

Fireplace::Fireplace(double X, double Y) : Instance(X, Y, 2, 2){
    solid = false;   
}

std::vector<int> Fireplace::initLayers(){
    layers.push_back(LAYER_NORMAL-1);
    return layers;
}
