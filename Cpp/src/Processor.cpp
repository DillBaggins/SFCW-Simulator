#include "Processor.h"

IQ_1D SignalProcessor::fft(IQ_1D timeSignal)
{
int N = timeSignal.size();
    fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    
    // Plan the FFT
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // populate the FFTW signal
    for(int i=0;i<N;i++){
        in[i][0]=timeSignal[i].real();
        in[i][1]=timeSignal[i].imag();
    }

    fftw_execute(plan);

    // put the values into the output vector
    IQ_1D result;
    for(int i=0;i<N;i++){
        result.push_back(IQ(out[i][0],out[i][1]));
    }

    // Clean up
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return result;
}

IQ_1D SignalProcessor::ifft(IQ_1D frequencySignal)
{
    int N = frequencySignal.size();
    fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    
    // Plan the FFT
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    // populate the FFTW signal
    for(int i=0;i<N;i++){
        in[i][0]=frequencySignal[i].real();
        in[i][1]=frequencySignal[i].imag();
    }

    fftw_execute(plan);

    // put the values into the output vector
    IQ_1D result;
    for(int i=0;i<N;i++){
        result.push_back(IQ(out[i][0],out[i][1]));
    }

    // Clean up
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return result;

}

std::vector<float> SignalProcessor::ExtractIChannel(const IQ_1D &input)
{
    std::vector<float> output;
    output.reserve(input.size());

    for (const auto& element : input) {
        output.push_back(element.real());
    }

    return output;
}


std::vector<float> SignalProcessor::ExtractQChannel(const IQ_1D &input)
{
    std::vector<float> output;
    output.reserve(input.size());

    for (const auto& element : input) {
        output.push_back(element.imag());
    }

    return output;
}

std::vector<float> SignalProcessor::GenerateTimeAxis(float timeLengthSeconds, float sampleRateHz)
{
    std::vector<float> output;
    int numElements = int(timeLengthSeconds*sampleRateHz);

    for (int i=0; i<numElements; i++){
        output.push_back(i*(1/sampleRateHz));
    }
    
    return output;
}
