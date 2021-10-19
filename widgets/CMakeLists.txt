cmake_minimum_required(VERSION 3.17.0)

add_subdirectory(gauge_indicator)
add_subdirectory(indicators)

add_library(Widgets SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compass.cpp
)

target_include_directories(Widgets
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Widgets
    PUBLIC
        GaugeIndicator
        FlightInstruments
    PRIVATE
        Qt5::Core
        Qt5::Widgets
)
