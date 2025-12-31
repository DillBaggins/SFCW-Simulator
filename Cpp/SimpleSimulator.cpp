#include "inc/Synthesiser.h"
#include "inc/Target.h"
#include <iostream>
#include "inc/Plotting.h"
#include "inc/Processor.h"
#include <thread>

#include <imgui.h>
#include <implot.h>

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <vector>
#include <complex>


GLFWwindow* InitWindow() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1200, 800, "SFCW Simulator", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return window;
}

void SimulatorThread(PlotData& plots, float fs) {
    float t = 0.0f;
    float dt = 1.0f / fs;
    float f = 1e3;

    while (true) {
        float i = std::cos(2.0f * M_PI * f * t);
        float q = std::sin(2.0f * M_PI * f * t);

        plots.time.Push(t);
        plots.I.Push(i);
        plots.Q.Push(q);

        t += dt;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main() {
    std::cout<<"Launching Simple Simulator"<<std::endl;

    // Make Synth and Get test sweep
    Synthesiser testSynth(900e6,20e3,10);
    Sweep initialSweep = testSynth.GenerateSweep();

    std::cout<<"Making Targets"<<std::endl;
    Target testTarget(70.0f);
    Target testTarget2(270.0f);

    std::cout<<"Sending sweep to targets"<<std::endl;
    Sweep shrunkSweep = testTarget.ApplyTransferFunction(initialSweep);
    Sweep shrunkSweep2 = testTarget2.ApplyTransferFunction(initialSweep);


    std::cout<<"Printing Details"<<std::endl;
    std::cout<<"target 1 produced reflection with gain of:  "<<shrunkSweep[3].m_phasor.GetMagnitude()<<" and phase of "<<shrunkSweep[3].m_phasor.GetPhaseDegrees()<<std::endl;
    std::cout<<"target 2 produced reflection with gain of:  "<<shrunkSweep2[3].m_phasor.GetMagnitude()<<" and phase of "<<shrunkSweep2[3].m_phasor.GetPhaseDegrees()<<std::endl;

    std::cout<<"Test Gain and Phase Shift"<<std::endl;
    shrunkSweep[3].m_phasor.ApplyPhaseShift(M_PI/4);
    shrunkSweep[3].m_phasor.ApplyGain(100);
    std::cout<<"target 1 produced reflection with gain of:  "<<shrunkSweep[3].m_phasor.GetMagnitude()<<" and phase of "<<shrunkSweep[3].m_phasor.GetPhaseDegrees()<<std::endl;

    // Lets test a simple plot
    FrequencyStep testStep = shrunkSweep[3];
    testStep.m_fFrequencyHz=10e3;

    
    IQ_1D timeDomain = testStep.GetTimeDomain(1,100e3);

    GLFWwindow* window = InitWindow();

    PlotData plotData;
    plotData.I.PushBulk(SignalProcessor::ExtractIChannel(timeDomain));
    plotData.Q.PushBulk(SignalProcessor::ExtractQChannel(timeDomain));
    plotData.time.PushBulk(SignalProcessor::GenerateTimeAxis(1,100e3));
    


    // std::thread simThread(SimulatorThread, std::ref(plotData), 10e3);
    // simThread.detach();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("SFCW Simulator");
        RenderIQPlots(plotData);
        ImGui::End();

        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
