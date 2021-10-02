#cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
#
#project(AirspeedIndicator)
#
#add_executable(AirspeedIndicator
#    ${CMAKE_CURRENT_SOURCE_DIR}/sources/airspeed_indicator_test.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/sources/airspeed_indicator.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/sources/airspeed_indicator_model.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/sources/airspeed_indicator_view.cpp
#
#    ${CMAKE_SOURCE_DIR}/indicators/src/indicator.cpp
#    ${CMAKE_SOURCE_DIR}/indicators/src/movable_linear_gauge.cpp
#    ${CMAKE_SOURCE_DIR}/indicators/src/level.cpp
#    ${CMAKE_SOURCE_DIR}/src/graphics_view.cpp
#    ${CMAKE_SOURCE_DIR}/src/graphics_scene.cpp
#)
#
#target_include_directories(AirspeedIndicator
#    PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/includes
#        ${CMAKE_SOURCE_DIR}/indicators/include
#        ${CMAKE_SOURCE_DIR}/include
#)
#
##find_package(Qt5OpenGL REQUIRED)
#
#target_link_libraries(AirspeedIndicator PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core)
#
##set_target_properties(AirspeedIndicator
##    PROPERTIES
##        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}"
##)
#
##target_compile_features(AirspeedIndicator
##   PRIVATE
##       cxx_std_14
##)
#
##target_compile_options(AirspeedIndicator PRIVATE -std=c++14)
#
#set_target_properties(AirspeedIndicator
#    PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#)
