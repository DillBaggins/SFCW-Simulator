#include "Simulator.h"

Simulator::Simulator(std::shared_ptr<SimulatorControl> pSimulatorcontrol, std::shared_ptr<AllPlotsData> pAllPlotsData, Synthesiser SignalGenerator):
m_pAllPlotsData(pAllPlotsData),
m_pSimulatorControl(pSimulatorcontrol),
m_SignalGenerator(SignalGenerator)
{
}

void Simulator::RunStep()
{
    // Do actual simulation here:

    PostPlots();
}

void Simulator::PostPlots()
{
    // Sweep Profile
    if (m_pAllPlotsData){
        m_pAllPlotsData->sweepProfile.frequency.Clear();
        m_pAllPlotsData->sweepProfile.time.Clear();

        Sweep currentSweep = m_SignalGenerator.GenerateSweep();
        for (int i =0 ; i<currentSweep.size(); i++){
            m_pAllPlotsData->sweepProfile.frequency.Push(currentSweep[i].m_fFrequencyHz);
            m_pAllPlotsData->sweepProfile.time.Push(i);
        }
    }

}

void Simulator::ChangeSynthesiser(Synthesiser newSynthesiser)
{
    m_SignalGenerator = newSynthesiser;
}

void Simulator::AddTarget(Target newTarget)
{
    m_vTargets.push_back(newTarget);
}

void Simulator::PopTarget()
{
    m_vTargets.pop_back();
}

void Simulator::AddTransmitComponent(Component newTransmitComponent)
{
    m_vTransmitComponents.push_back(newTransmitComponent);
}

void Simulator::AddReceiveComponent(Component newReceiveComponent)
{
    m_vReceiveComponents.push_back(newReceiveComponent);
}

void Simulator::RemoveAllComponents()
{
    m_vReceiveComponents.clear();
    m_vTransmitComponents.clear();
}

void Simulator::RemoveAllTargets()
{
    m_vTargets.clear();
}
