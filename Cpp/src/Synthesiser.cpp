#include "Synthesiser.h"
#include <iostream>

Synthesiser::Synthesiser(float initialFrequencyHz, float stepSizeHz, int numSteps):
m_fStartingFrequencyHz(initialFrequencyHz),
m_fStepSizeHz(stepSizeHz),
m_iNumSteps(numSteps)
{}

Sweep Synthesiser::GenerateSweep()
{
    std::cout<<"Generating Sweep"<<std::endl;

    Sweep outputSweep;

    for (int i=0; i<m_iNumSteps; i++){
        FrequencyStep newStep(m_fStartingFrequencyHz+i*m_fStepSizeHz);
        outputSweep.push_back(newStep);        
    }

    return outputSweep;
}
