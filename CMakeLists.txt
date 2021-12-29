cmake_minimum_required(VERSION 3.12)

project(CSNetworkEmulator LANGUAGES C CXX)

set(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_MIN_VERSION 5.6.0)
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Widgets OpenGL Quick)
set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Quick)

add_definitions(${QT_DEFINITIONS})

add_subdirectory(src)
