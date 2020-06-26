#ifndef dos_obj_instcreate
#define dos_obj_instcreate

#include "instance.h"

/**
 * Honestly, this class is kind of a wrapper class to add stuff to a linked list.
 * This is an empty invisible instance whose only use is to add instances to the end of a level's drawing program.
 */
class InstCreate : public Instance {
    public:
        /// Constructor for an InstCreate
        InstCreate();
        /**
         * Blank draw command to do nothing.
         * @param gld GLUtil's draw functions.
         * @param gls GLUtil's shader functions.
         */
        void draw(GLDraw* gld, GLShaders* gls);
        /**
         * Something to add to the instance list.
         * @param i The instance to add to the level.
         */
        void addInstance(Instance* i);
};

#endif