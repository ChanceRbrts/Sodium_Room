#ifndef sdr_jung_getflash
#define sdr_jung_getflash

#include "../level.h"

class FlashlightArea : public Level{
    private:
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
    public:
        FlashlightArea();
};

#endif