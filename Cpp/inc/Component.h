#ifndef __COMPONENT_H
#define __COMPONENT_H

#include "Types.h"

// Base class
class Component{
    public:
        virtual Sweep ApplyTransferFunction(const Sweep input);
};


#endif