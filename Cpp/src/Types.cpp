#include "Types.h"

Phasor::Phasor():
m_IQData{}
{
}

Phasor::Phasor(float fMagnitude, float fPhaseDeg)
: m_IQData(
        fMagnitude * std::cos(fPhaseDeg * M_PI / 180.0f),
        fMagnitude * std::sin(fPhaseDeg * M_PI / 180.0f)
      )
{}

Phasor::Phasor(IQ IQData)
{
    m_IQData=IQ(IQData);
}


float Phasor::GetMagnitude() const
{
    return std::abs(m_IQData);
}

float Phasor::GetPhaseDegrees() const
{
    return GetPhaseRad() * 180.0f / M_PI;}

float Phasor::GetPhaseRad() const
{
    return atan2(m_IQData.imag(),m_IQData.real());
}


void Phasor::ApplyGain(const float gain_dB)
{
    float gainLinear = std::pow(10.0f,gain_dB/20.0f);
    m_IQData *= gainLinear;

}

void Phasor::ApplyPhaseShift(const float phaseRad)
{    
    m_IQData *= IQ(std::cos(phaseRad), std::sin(phaseRad));
}

FrequencyStep::FrequencyStep(float frequencyHz):
m_fFrequencyHz(frequencyHz),
m_phasor(1,0)
{
}

FrequencyStep::FrequencyStep(float frequencyHz, Phasor phasor):
m_fFrequencyHz(frequencyHz),
m_phasor(phasor)
{
}

IQ_1D FrequencyStep::GetTimeDomain(float lengthSeconds, float samplingRateHz)
{
    size_t numSamples = static_cast<size_t>(lengthSeconds * samplingRateHz);
    IQ_1D signal(numSamples);

    float baseMag = m_phasor.GetMagnitude();
    float basePhase = m_phasor.GetPhaseRad();

    for (size_t n = 0; n < numSamples; ++n) {
        float t = static_cast<float>(n) / samplingRateHz;
        float instantaneousPhase = 2.0f * M_PI * m_fFrequencyHz * t + basePhase + m_fPhaseNoise;
        float instantaneousMag = baseMag + m_fAmplitudeNoise;

        signal[n] = std::polar(instantaneousMag, instantaneousPhase);
    }

    return signal;
}
