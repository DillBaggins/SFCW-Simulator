#include "Target.h"

Target::Target(float rangeMeters):
m_fRangeMeters(rangeMeters)
{
}

Sweep Target::ApplyTransferFunction(const Sweep inputSweep)
{
    Sweep outputSweep = inputSweep;

    for (FrequencyStep& step : outputSweep){
        step.m_phasor.ApplyGain(GetAttenuationFromRange_dB(m_fRangeMeters));
    }
    
    return outputSweep;
}

float Target::GetAttenuationFromRange_dB(float rangeMeters)
{
    return 20*log10(1/(pow(4*M_PI,3)*pow(rangeMeters,4)));
}
