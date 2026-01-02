#ifndef __TARGET_H
#define __TARGET_H

#include "Types.h"
#include "Component.h"

/**
 * Base Class: Has a simple complex reflection coefficient that is not frequency-dependant
 */
class Target : Component {
    public:
        Target(float rangeMeters);
        Target(float rangeMeters, Phasor phasorReflectionCoefficient);

    public:
        Sweep ApplyTransferFunction(const Sweep inputSweep) override;
        
        static float GetAttenuationFromRange_dB(float rangeMeters);

    private:
        float m_fRangeMeters;
        Phasor m_PhasorReflectionCoefficient;

};

#endif