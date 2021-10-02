cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(AttitudeIndicator)

add_executable(AttitudeIndicator
    ${CMAKE_CURRENT_SOURCE_DIR}/src/attitude_indicator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/attitude_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/attitude_indicator_view.cpp

    ${CMAKE_SOURCE_DIR}/indicators/src/indicator.cpp
    ${CMAKE_SOURCE_DIR}/indicators/src/movable_linear_gauge.cpp
    ${CMAKE_SOURCE_DIR}/indicators/src/level.cpp
    ${CMAKE_SOURCE_DIR}/src/graphics_view.cpp
    ${CMAKE_SOURCE_DIR}/src/graphics_scene.cpp
)

target_include_directories(AttitudeIndicator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_SOURCE_DIR}/indicators/include
        ${CMAKE_SOURCE_DIR}/include
)

#find_package(Qt5OpenGL REQUIRED)

target_link_libraries(AttitudeIndicator PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core)

#set_target_properties(AttitudeIndicator
#    PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
#)

#target_compile_features(AttitudeIndicator
#   PRIVATE
#       cxx_std_14
#)

#target_compile_options(AttitudeIndicator PRIVATE -std=c++14)

set_target_properties(AttitudeIndicator
    PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
