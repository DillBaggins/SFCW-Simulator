#include "Plotting.h"

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
