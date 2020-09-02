#ifndef dwr_testMultipleLights
#define dwr_testMultipleLights

#include "../level.h"
#include "../../instances.h"

class TestMultipleLights : public Level {
    private:
      std::vector<Instance *> makeLevel(std::vector<Instance*> previous);
   public:
      TestMultipleLights();
      std::vector<Arc *> createArcs();
};

#endif