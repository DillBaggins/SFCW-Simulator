cmake_minimum_required(VERSION 3.5.1)
project(SFCWSimulator CXX C)

#!## Configure Compiler ########################################################
set(CMAKE_CXX_STANDARD 17)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)



#!###################################################### HDF LIBRARY #######################################################
set(HDF5_INCLUDE_DIRS /usr/include/hdf5/serial)
set(HDF5_LIBRARIES /usr/lib/x86_64-linux-gnu/hdf5/serial)
include_directories(${HDF5_INCLUDE_DIRS})
link_directories(${HDF5_LIBRARIES})


#!###################################################### HighFive LIBRARY #######################################################
add_subdirectory(${EXTERNAL_DIR}/HighFive)
include_directories(${EXTERNAL_DIR}/HighFive/include)

#!###################################################### BOOST LIBRARY THINGS #######################################################


# This example also requires Boost.
# Set components here, then include UHDBoost to do the actual finding
#set(BOOST_MIN_VERSION 1.65)
find_package(Boost REQUIRED iostreams system filesystem)  # <- using default cmake find script. It works best

message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
message(STATUS "Boost Found: ${Boost_FOUND}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

include_directories(
    ${Boost_INCLUDE_DIRS}
)

#!###################################################### FFTW #######################################################
include(ExternalProject)

MESSAGE(STATUS "Trying to install fftw...")

ExternalProject_Add(project_fftw
  #GIT_REPOSITORY  https://github.com/FFTW/fftw3
  URL http://www.fftw.org/fftw-3.3.10.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/fftw
  CONFIGURE_COMMAND
${CMAKE_CURRENT_BINARY_DIR}/fftw/src/project_fftw/configure
--prefix=${CMAKE_CURRENT_BINARY_DIR}/fftw/install
  INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/fftw/install
  DOWNLOAD_EXTRACT_TIMESTAMP FALSE
  )

add_library(fftw STATIC IMPORTED)
set(lib_fftw_name
${CMAKE_STATIC_LIBRARY_PREFIX}fftw3${CMAKE_STATIC_LIBRARY_SUFFIX})
set_target_properties(fftw PROPERTIES IMPORTED_LOCATION
${CMAKE_CURRENT_BINARY_DIR}/fftw/install/lib/${lib_fftw_name})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/fftw/install/include)

#!###################################################### IMGUI #######################################################

add_library(imgui
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
    external/implot/implot.cpp
    external/implot/implot_items.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
    external/implot
)

target_link_libraries(imgui PUBLIC glfw GL)


#!###################################################### My Libraries #######################################################
# ---- Your library ----
add_library(sfcw_core
    src/Types.cpp
    src/Component.cpp
    src/Processor.cpp
    src/Plotting.cpp
    src/Synthesiser.cpp
    src/Target.cpp
    src/Simulator.cpp
)
target_include_directories(sfcw_core PUBLIC inc)

target_link_libraries(sfcw_core
    ${HDF5_LIBRARIES}
    Boost::iostreams
    HighFive
    fftw
    imgui
)

#!###################################################### Making Executable #######################################################


add_executable(${PROJECT_NAME} 
  main.cpp
)

add_dependencies(${PROJECT_NAME} project_fftw)

target_link_libraries(${PROJECT_NAME} sfcw_core imgui)
