#ifndef __PLOTTING_H
#define __PLOTTING_H

#include <vector>
#include <complex>
#include <mutex>
#include "implot.h"

// -----------------------------
// AsyncPlotBuffer
// -----------------------------
template<typename T>
class AsyncPlotBuffer {
public:
    void Push(const T& value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data.push_back(value);
    }

    void PushBulk(const std::vector<T>& values) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data.insert(m_data.end(), values.begin(), values.end());
    }

    std::vector<T> Snapshot() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_data;
    }

    void Clear() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data.clear();
    }

private:
    mutable std::mutex m_mutex;
    std::vector<T> m_data;
};

// -----------------------------
// PlotData
// -----------------------------
struct PlotData {
    AsyncPlotBuffer<float> time;
    AsyncPlotBuffer<float> I;
    AsyncPlotBuffer<float> Q;
};

// -----------------------------
// Rendering API
// -----------------------------
void RenderIQPlots(PlotData& plots);

#endif
