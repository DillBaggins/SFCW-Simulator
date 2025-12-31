#ifndef __SYNTHESISER_H
#define __SYNTHESISER_H

#include "Types.h"

class Synthesiser{
    public:
        Synthesiser(float initialFrequencyHz, float stepSizeHz, int numSteps);

        Sweep GenerateSweep();
        
    private:
        float m_fStartingFrequencyHz;
        float m_fStepSizeHz;
        int m_iNumSteps;
};

#endif