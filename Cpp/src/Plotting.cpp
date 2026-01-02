#include "Plotting.h"
#include "SimulatorControl.h"
#include <imgui.h>
#include <iostream>

void RenderIQPlots(PlotData& plots)
{
    auto t = plots.time.Snapshot();
    auto I = plots.I.Snapshot();
    auto Q = plots.Q.Snapshot();

    if (t.empty()) return;

    if (ImPlot::BeginPlot("IQ Channels", ImVec2(-1, 400))) {
        ImPlot::SetupAxes("Time (s)", "Amplitude");
        ImPlot::PlotLine("I", t.data(), I.data(), t.size());
        ImPlot::PlotLine("Q", t.data(), Q.data(), t.size());
        ImPlot::EndPlot();
    }
}

void RenderFrequencyProfile(SweepProfileData &plots)
{
    auto time = plots.time.Snapshot();
    auto frequency = plots.frequency.Snapshot();
    if (time.empty() || frequency.empty()) return;

     if (ImPlot::BeginPlot("Frequency Profile", ImVec2(-1, 400))) {
        ImPlot::SetupAxes("Time (s)", "Frequency");
        ImPlot::PlotStairs("Frequency", time.data(), frequency.data(), time.size());
        ImPlot::EndPlot();
    }

}

void RenderSimulatorControls(SimulatorControl* ctrl)
{
    ImGui::SeparatorText("Simulation Control");

    // Run / Pause toggle
    bool run = ctrl->run.load();
    if (ImGui::Checkbox("Run Simulator", &run)) {
        ctrl->run.store(run);
    }

    // Signal generator
    ImGui::SeparatorText("Waveform");
    static float initialFreqHz = 0.0f;
    static float stepSizeHz = 0.0f;
    static int numSteps = 0.0f;
    ImGui::InputFloat("Lower  Freuncy (Hz)", &initialFreqHz);
    ImGui::InputFloat("Step Size (Hz)", &stepSizeHz);
    ImGui::InputInt("Num Steps", &numSteps);
    if (ImGui::Button("Change Waveform")) {
        std::cout<<"Changing Waveform"<<std::endl;
    }


    // Target 
    ImGui::SeparatorText("Add Target");
    static float range_m = 100.0f;
    static float refl_mag = 0.5f;
    static float refl_phase = 0.0f;
    ImGui::InputFloat("Range (m)", &range_m);
    ImGui::InputFloat("Reflection Mag", &refl_mag);
    ImGui::InputFloat("Reflection Phase (deg)", &refl_phase);
    if (ImGui::Button("Add Target")) {
        std::lock_guard<std::mutex> lock(ctrl->target_mutex);
        ctrl->targets.push_back({range_m, refl_mag, refl_phase});
    }

    
    // View
    ImGui::SeparatorText("View");
    static int view_idx = 0;
    const char* views[] = {
        "Sweep Profile",
        "Range profile"
    };

    if (ImGui::Combo("View Mode", &view_idx, views, IM_ARRAYSIZE(views))) {
        ctrl->view.store(static_cast<ViewMode>(view_idx));
    }
}

