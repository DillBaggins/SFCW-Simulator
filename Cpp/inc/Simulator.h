#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include "Types.h"
#include "Synthesiser.h"
#include "Target.h"
#include "Processor.h"
#include <functional>
#include "Component.h"
#include <atomic>
#include "SimulatorControl.h"
#include <memory>
#include "Plotting.h"

class Simulator{

public:

    Simulator(std::shared_ptr<SimulatorControl> pSimulatorcontrol, std::shared_ptr<AllPlotsData> pAllPlotsData, Synthesiser SignalGenerator);

    void RunStep();

    void PostPlots();

    void ChangeSynthesiser(Synthesiser newSynthesiser);

    void AddTarget(Target newTarget);

    void PopTarget();

    void AddTransmitComponent(Component newTransmitComponent);

    void AddReceiveComponent(Component newReceiveComponent);

    void RemoveAllComponents();

    void RemoveAllTargets();


private:
    std::shared_ptr<SimulatorControl> m_pSimulatorControl; 
    std::shared_ptr<AllPlotsData>  m_pAllPlotsData;

    std::vector<Target> m_vTargets;
    Synthesiser m_SignalGenerator;
    std::vector<Component> m_vTransmitComponents;
    std::vector<Component> m_vReceiveComponents;
    std::atomic<bool> m_bReadyToRun;
};


#endif