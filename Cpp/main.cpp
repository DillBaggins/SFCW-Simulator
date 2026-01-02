#include "inc/Synthesiser.h"
#include "inc/Target.h"
#include <iostream>
#include "inc/Plotting.h"
#include "inc/Processor.h"
#include "inc/SimulatorControl.h"
#include "inc/Simulator.h"
#include <thread>

#include <imgui.h>
#include <implot.h>

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <vector>
#include <complex>
#include <atomic>
#include <memory>

std::atomic<bool> g_bRunning{true};

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

void SimulatorThread(std::shared_ptr<Simulator> pSimulator)
{
    while (g_bRunning.load()) {

        pSimulator->RunStep();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}


int main() {
    std::cout<<"Launching Simple Simulator"<<std::endl;

    GLFWwindow* window = InitWindow();

    std::shared_ptr<SimulatorControl> pSimulatorContol = std::make_shared<SimulatorControl>();

    std::shared_ptr<AllPlotsData> pAllPlotsData = std::make_shared<AllPlotsData>();

    Synthesiser dummySynthesiser(100,10,20);

    std::shared_ptr<Simulator> pSimulator = std::make_shared<Simulator>(pSimulatorContol,pAllPlotsData,dummySynthesiser);

    std::thread simThread(SimulatorThread, pSimulator);



    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("SFCW Simulator");
        RenderSimulatorControls(pSimulatorContol.get());
        RenderFrequencyProfile(pAllPlotsData->sweepProfile);
        ImGui::End();

        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    g_bRunning.store(false);

    
    if(simThread.joinable()){
        simThread.join();
    }
    
    glfwTerminate();
}
