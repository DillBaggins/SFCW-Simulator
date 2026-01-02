#ifndef __TYPES_H
#define __TYPES_H

#include <complex>
#include <vector>
#include <math.h>

typedef std::complex<float> IQ;
typedef std::vector<IQ> IQ_1D;
typedef std::vector<IQ_1D> IQ_2D; 

class Phasor{
    public: 
        // Constructors
        Phasor();
        Phasor(float fMagnitude, float fPhaseDeg);
        Phasor(IQ IQData);
        ~Phasor() = default;

        // Getters 
        float GetMagnitude() const;
        float GetMagnitude_dB() const;
        float GetPhaseDegrees() const;
        float GetPhaseRad() const;

        // Modifiers
        void ApplyGain_dB(const float gain_dB);
        void ApplyPhaseShiftRad(const float phaseRad);

    private: 
        IQ m_IQData;
};

class FrequencyStep{
    public:
        FrequencyStep(float frequencyHz);
        FrequencyStep(float frequencyHz, Phasor phasor);

        IQ_1D GetTimeDomain(float samplingRateHz);
    public:
        float m_fFrequencyHz=0;
        float m_fIntededFrequencyHz=0;
        float m_fTransmitTimeSeconds=0.0f;
        Phasor m_phasor{};
        float m_fPhaseNoise=0;
        float m_fAmplitudeNoise=0;
};

typedef std::vector<FrequencyStep> Sweep;




#endif