cmake_minimum_required(VERSION 3.12)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH})

qt5_add_resources(RESOURCES "resources/main.qrc")

file(GLOB_RECURSE MODELS_SRCS "models/*.cxx")
file(GLOB_RECURSE MODELS_HEADERS "models/*.h")

file(GLOB DEVICES_SRCS "devices/*.cxx")
file(GLOB DEVICES_HEADERS "devices/*.h")

file(GLOB MANAGERS_SRCS "managers/*.cxx")
file(GLOB MANAGERS_HEADERS "managers/*.h")

set(SRCS ${MODELS_SRCS}
         ${DEVICES_SRCS}
         ${MANAGERS_SRCS}
         entry.cxx)

set(HEADERS ${MODELS_HEADERS}
            ${DEVICES_HEADERS}
            ${MANAGERS_HEADERS})

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
