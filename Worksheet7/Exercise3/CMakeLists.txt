cmake_minimum_required(VERSION 3.16)

project(worksheet6 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# VTK (Qt-enabled install)
# Worksheet7 requirement: use VTK REQUIRED (no per-module list)
find_package(VTK REQUIRED)

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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(worksheet6
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ModelPartList.cpp
        icons.qrc
        optionaldialog.h optionaldialog.cpp optionaldialog.ui
    )
else()
    if(ANDROID)
        add_library(worksheet6 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(worksheet6
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(worksheet6 PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  ${VTK_LIBRARIES}
)

# Make sure QVTKOpenGLNativeWidget.h can be found (use the Qt-enabled VTK install)
target_include_directories(worksheet6 PRIVATE
  "C:/VTK_Install_Qt/include/vtk-9.6"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.worksheet6)
endif()
set_target_properties(worksheet6 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Copy across OpenVR bindings that map controllers
# The program will expect to find these in the build dir when it runs
add_custom_target(VRBindings)

add_custom_command(TARGET VRBindings PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/vrbindings
          ${CMAKE_BINARY_DIR}/vrbindings
)

# Ensure vrbindings get copied whenever worksheet6 is built
add_dependencies(worksheet6 VRBindings)

include(GNUInstallDirs)
install(TARGETS worksheet6
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(worksheet6)
endif()