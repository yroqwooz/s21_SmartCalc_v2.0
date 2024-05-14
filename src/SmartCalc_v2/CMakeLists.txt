cmake_minimum_required(VERSION 3.5)

project(SmartCalc_v2 VERSION 0.1 LANGUAGES CXX)
# project(SmartCalc_tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(QCustomPlot)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core PrintSupport Gui REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        scview.cpp
        scview.h
        scview.ui
        sccontroller.cpp
        sccontroller.h
        scmodel.cpp
        scmodel.h
        plotwindow.h
        plotwindow.cpp
        plotwindow.ui
        CreditCalc/cccontroller.cpp
        CreditCalc/cccontroller.h
        CreditCalc/ccmodel.cpp
        CreditCalc/ccmodel.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc_v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        sccontroller.h sccontroller.cpp
        scmodel.h scmodel.cpp
        scview.h scview.cpp

        plotwindow.h plotwindow.cpp plotwindow.ui
        QCustomPlot/CMakeLists.txt QCustomPlot/lib/qcustomplot.h QCustomPlot/lib/config.h.in QCustomPlot/lib/qcustomplot.cpp QCustomPlot/lib/config.h QCustomPlot/lib/CMakeLists.txt
        CreditCalc/cccontroller.h CreditCalc/cccontroller.cpp
        CreditCalc/ccmodel.h CreditCalc/ccmodel.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalc_v2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalc_v2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalc_v2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalc_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SmartCalc_v2 PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(SmartCalc_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Gui)

target_link_libraries(${PROJECT_NAME} PRIVATE qcustomplot)
target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_USE_LIBRARY)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SmartCalc_v2)
endif()
set_target_properties(SmartCalc_v2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    WIN64_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SmartCalc_v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc_v2)
endif()
