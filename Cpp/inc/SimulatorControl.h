#ifndef __SIMULATOR_CONTROL_H
#define __SIMULATOR_CONTROL_H

#include <atomic>
#include <mutex>
#include <vector>

struct TargetParams {
    float range_m = 0.0f;
    float refl_mag = 1.0f;
    float refl_phase_deg = 0.0f;
};

enum class ViewMode {
    Sweep,
    RangeProfile
};

struct SimulatorControl {
    
    // Running Yes/No
    std::atomic<bool> run{false};

    // Signal Generator Parameters
    float fStartingFrequencyHz;
    float fStepFrequencyHz; 
    int iNumSteps;
    std::atomic<bool> updateSynthesiser;

    // Targets 
    std::mutex target_mutex;
    std::vector<TargetParams> targets;

    // Viewmode (not currently being used)
    std::atomic<ViewMode> view{ViewMode::Sweep};
};



#endif