cmake_minimum_required(VERSION 3.20)
project(Worksheet7_VTK_App LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(VTK REQUIRED COMPONENTS
  CommonCore
  FiltersSources
  RenderingCore
  RenderingOpenGL2
  InteractionStyle
)

add_executable(Worksheet7_VTK_App main.cpp)

target_link_libraries(Worksheet7_VTK_App PRIVATE
  VTK::CommonCore
  VTK::FiltersSources
  VTK::RenderingCore
  VTK::RenderingOpenGL2
  VTK::InteractionStyle
)

vtk_module_autoinit(
  TARGETS Worksheet7_VTK_App
  MODULES
    VTK::CommonCore
    VTK::FiltersSources
    VTK::RenderingCore
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
)