cmake_minimum_required(VERSION 3.5)

project(Regular LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)


set(CMAKE_PREFIX_PATH "/Users/yronwooz/Qt/6.1.0/clang_64")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Object Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


if ($ENV{GOOGLETEST_DIR})
    get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
elseif (EXISTS "") # set by QC
    get_filename_component(_GTEST_BASE "" REALPATH) # set by QC
endif()

if (NOT GTEST_ROOT)
    if (_GTEST_BASE)
        message("Setting GTEST_ROOT to ${_GTEST_BASE}")
        set(GTEST_ROOT ${_GTEST_BASE})
    else()
        message("No GTEST_ROOT specified - using system defaults.")
    endif()
endif()

find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message (FATAL_ERROR "No GTest Found")
endif()

add_executable(Regular
    main.cpp
    tst_regular.cpp
    ../SmartCalc_v2/sccontroller.h
    ../SmartCalc_v2/sccontroller.cpp
    ../SmartCalc_v2/scmodel.h
    ../SmartCalc_v2/scmodel.cpp
)
add_test(NAME Regular COMMAND Regular)


target_include_directories(Regular
    PUBLIC ../SmartCalc_v2
)

target_link_libraries(Regular PRIVATE GTest::GTest)
target_link_libraries(Regular PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (GMock_FOUND)
    target_link_libraries(Regular INTERFACE GTest::GMock)
endif()
