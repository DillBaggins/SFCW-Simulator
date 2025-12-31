#ifndef __TARGET_H
#define __TARGET_H

#include "Types.h"
#include "Component.h"

/**
 * Base Class: Has a simple reflection coefficient and no phase interaction
 */

class Target : Component {
    public:
        Target(float rangeMeters);

    public:
        Sweep ApplyTransferFunction(const Sweep inputSweep) override;
        
        static float GetAttenuationFromRange_dB(float rangeMeters);

    private:
        float m_fRangeMeters;
};

#endif