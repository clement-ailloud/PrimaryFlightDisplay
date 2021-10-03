add_library(FlightInstruments
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/airspeed_indicator/src/airspeed_indicator_view.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/attitude_indicator/src/attitude_indicator_view.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/altitude_indicator/src/altitude_indicator_view.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/heading_indicator/src/heading_indicator_view.cpp
)

target_include_directories(FlightInstruments
    PUBLIC
        ${CMAKE_SOURCE_DIR}/primary_flight_display/include
        ${CMAKE_CURRENT_SOURCE_DIR}/airspeed_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/attitude_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/altitude_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/heading_indicator/include
)

target_link_libraries(FlightInstruments
    PRIVATE
        Common
        GaugeIndicator
	Qt5::Widgets
)

set_target_properties(FlightInstruments
    PROPERTIES
	CXX_STANDARD 17
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON
)

#install(TARGETS FlightInstruments
#   EXPORT PrimaryFlightDisplayIndicatorTargets
#    LIBRARY    DESTINATION   lib
#    ARCHIVE    DESTINATION   lib
#    RUNTIME    DESTINATION   bin
#    INCLUDES   DESTINATION   include
#)

#install(EXPORT PrimaryFlightDisplayIndicatorTargets
#    FILE          PrimaryFlightDisplayIndicatorTargets.cmake
#    NAMESPACE     FlightInstruments::
#    DESTINATION   lib/cmake/PrimaryFlightDisplay
#)
