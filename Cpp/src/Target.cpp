#include "Target.h"

Target::Target(float rangeMeters):
m_fRangeMeters(rangeMeters),
m_PhasorReflectionCoefficient(IQ(std::polar(1.0f,0.0f)))
{
}

Target::Target(float rangeMeters, Phasor phasorReflectionCoefficient):
m_fRangeMeters(rangeMeters),
m_PhasorReflectionCoefficient(phasorReflectionCoefficient)
{
}

Sweep Target::ApplyTransferFunction(const Sweep inputSweep)
{
    Sweep outputSweep = inputSweep;

    for (FrequencyStep& step : outputSweep){
        step.m_phasor.ApplyGain_dB(GetAttenuationFromRange_dB(m_fRangeMeters));
        step.m_phasor.ApplyGain_dB(m_PhasorReflectionCoefficient.GetMagnitude_dB());
        step.m_phasor.ApplyPhaseShiftRad(m_PhasorReflectionCoefficient.GetPhaseRad());
    }
    
    return outputSweep;
}

float Target::GetAttenuationFromRange_dB(float rangeMeters)
{
    return 20*log10(1/(pow(4*M_PI,3)*pow(rangeMeters,4)));
}
