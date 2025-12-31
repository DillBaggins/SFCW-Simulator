#ifndef __SIGNAL_PROCESSOR_H
#define __SIGNAL_PROCESSOR_H



#include "Types.h"
#include <vector>
#include <complex>
#include <iostream>
#include <fftw3.h>


class SignalProcessor{
public:
    static IQ_1D fft(IQ_1D timeSignal);
    
    static IQ_1D ifft(IQ_1D frequencySignal);

    static std::vector<float> ExtractIChannel(const IQ_1D& input);

    static std::vector<float> ExtractQChannel(const IQ_1D& input);
    
    static std::vector<float> GenerateTimeAxis(float timeLengthSeconds, float sampleRateHz);
    
  
};


#endif