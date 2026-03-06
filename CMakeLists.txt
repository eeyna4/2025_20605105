cmake_minimum_required(VERSION 3.20)

project(Exercise3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ---- Qt (use Qt6 directly; you pass -DQt6_DIR=...) ----
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

# ---- VTK ----
find_package(VTK REQUIRED COMPONENTS
  CommonCore
  CommonDataModel
  IOGeometry
  FiltersCore
  FiltersSources
  RenderingCore
  RenderingOpenGL2
  RenderingUI
  InteractionStyle
  RenderingQt
  GUISupportQt
)

set(PROJECT_SOURCES
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  ModelPart.cpp
  ModelPart.h
  ModelPartList.cpp
  ModelPartList.h
  optionaldialog.cpp
  optionaldialog.h
  optionaldialog.ui
  icons.qrc
)

qt_add_executable(${PROJECT_NAME}
  MANUAL_FINALIZATION
  ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt6::Widgets
  Qt6::OpenGLWidgets
  ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS ${PROJECT_NAME}
  MODULES ${VTK_LIBRARIES}
)

add_custom_target(VRBindings ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/vrbindings
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/vrbindings
)
add_dependencies(${PROJECT_NAME} VRBindings)

set_target_properties(${PROJECT_NAME} PROPERTIES
  WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(${PROJECT_NAME})
endif()