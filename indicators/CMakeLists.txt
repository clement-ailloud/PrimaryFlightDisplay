
set(INDICATOR_MODEL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/indicator_model.cpp
)

set(AIRSPEED_INDICATOR_SOURCES
    #${CMAKE_CURRENT_SOURCE_DIR}/airspeed_indicator/src/airspeed_indicator.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/airspeed_indicator/src/airspeed_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/airspeed_indicator/src/airspeed_indicator_view.cpp
)

set(ATTITUDE_INDICATOR_SOURCES
    #${CMAKE_CURRENT_SOURCE_DIR}/attitude_indicator/src/attitude_indicator.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/attitude_indicator/src/attitude_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/attitude_indicator/src/attitude_indicator_view.cpp
)

set(ALTITUDE_INDICATOR_SOURCES
    #${CMAKE_CURRENT_SOURCE_DIR}/altitude_indicator/src/attitude_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/altitude_indicator/src/altitude_indicator_view.cpp
)

set(HEADING_INDICATOR_SOURCES
    #${CMAKE_CURRENT_SOURCE_DIR}/altitude_indicator/src/attitude_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/heading_indicator/src/heading_indicator_view.cpp
)

set(LINEAR_GAUGE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tick.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/linear_gauge_value.cpp
)

add_library(PrimaryFlightDisplayIndicator
    SHARED
        ${AIRSPEED_INDICATOR_SOURCES}
        ${ATTITUDE_INDICATOR_SOURCES}
        ${ALTITUDE_INDICATOR_SOURCES}
        ${HEADING_INDICATOR_SOURCES}
        #${INDICATOR_MODEL_SOURCES}
)

target_include_directories(PrimaryFlightDisplayIndicator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/airspeed_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/attitude_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/altitude_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/heading_indicator/include
        ${CMAKE_SOURCE_DIR}/primary_flight_display/include
)

target_link_libraries(PrimaryFlightDisplayIndicator
    PRIVATE
        Common
        LinearGauge
	Qt5::Widgets
)

set_target_properties(PrimaryFlightDisplayIndicator
    PROPERTIES
        #DEBUG_POSTFIX "-debug"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>

	CXX_STANDARD 17
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON

        LINKER_LANGUAGE     CXX
        #LINK_WHAT_YOU_USE   TRUE
)

#set(INERTIAL_MEASUREMENT_UNIT_SOURCES
#    ${CMAKE_CURRENT_SOURCE_DIR}/imu/src/imu_model.cpp
#)

#install(TARGETS PrimaryFlightDisplayIndicator
#   EXPORT PrimaryFlightDisplayIndicatorTargets
#    LIBRARY    DESTINATION   lib
#    ARCHIVE    DESTINATION   lib
#    RUNTIME    DESTINATION   bin
#    INCLUDES   DESTINATION   include
#)

#install(EXPORT PrimaryFlightDisplayIndicatorTargets
#    FILE          PrimaryFlightDisplayIndicatorTargets.cmake
#    NAMESPACE     PrimaryFlightDisplayIndicator::
#    DESTINATION   lib/cmake/PrimaryFlightDisplay
#)
