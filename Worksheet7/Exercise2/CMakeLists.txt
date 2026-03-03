cmake_minimum_required(VERSION 3.20)
project(Worksheet7_Exercise2_VR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(VTK REQUIRED COMPONENTS
  CommonCore
  FiltersSources
  RenderingCore
  RenderingOpenGL2
  InteractionStyle
  RenderingOpenVR
)

add_executable(Worksheet7_Exercise2_VR main.cpp)

target_link_libraries(Worksheet7_Exercise2_VR PRIVATE
  VTK::CommonCore
  VTK::FiltersSources
  VTK::RenderingCore
  VTK::RenderingOpenGL2
  VTK::InteractionStyle
  VTK::RenderingOpenVR
)

vtk_module_autoinit(
  TARGETS Worksheet7_Exercise2_VR
  MODULES
    VTK::CommonCore
    VTK::FiltersSources
    VTK::RenderingCore
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
    VTK::RenderingOpenVR
)