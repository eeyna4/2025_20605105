cmake_minimum_required(VERSION 3.16)

project(worksheet6 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# VTK (no GUISupportQt in your local VTK build)
find_package(VTK REQUIRED COMPONENTS
  CommonCore
  FiltersSources
  RenderingCore
  RenderingOpenGL2
  InteractionStyle
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
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(worksheet6
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ModelPartList.cpp
        icons.qrc
        optionaldialog.h optionaldialog.cpp optionaldialog.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET worksheet6 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(worksheet6 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(worksheet6
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(worksheet6 PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  VTK::CommonCore
  VTK::FiltersSources
  VTK::RenderingCore
  VTK::RenderingOpenGL2
  VTK::InteractionStyle
)

vtk_module_autoinit(
  TARGETS worksheet6
  MODULES
    VTK::CommonCore
    VTK::FiltersSources
    VTK::RenderingCore
    VTK::RenderingOpenGL2
    VTK::InteractionStyle
)

# Make sure QVTKOpenGLNativeWidget.h can be found
# (VTK_DIR is set by Qt Creator's CMake config; headers live in VTK install include folder)
target_include_directories(worksheet6 PRIVATE
  "C:/Program Files (x86)/VTK/include/vtk-9.6"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
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

include(GNUInstallDirs)
install(TARGETS worksheet6
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(worksheet6)
endif()