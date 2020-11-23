#ifndef sdr_jung_flashexit
#define sdr_jung_flashexit

#include "../level.h"
#include "../../instancesExt.h"

class FlashlightExit : public Level{
    private:
        Level* enclosed;
        std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
    public:
        FlashlightExit();
};

#endif