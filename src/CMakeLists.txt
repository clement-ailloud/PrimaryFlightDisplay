cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(AIRSPEED_INDICATOR_SOURCES
    #${CMAKE_CURRENT_SOURCE_DIR}/indicators/airspeed_indicator/src/airspeed_indicator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indicators/airspeed_indicator/src/airspeed_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indicators/airspeed_indicator/src/airspeed_indicator_view.cpp
)

set(ATTITUDE_INDICATOR_SOURCES
    #${CMAKE_CURRENT_SOURCE_DIR}/indicators/attitude_indicator/src/attitude_indicator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indicators/attitude_indicator/src/attitude_indicator_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/indicators/attitude_indicator/src/attitude_indicator_view.cpp
)

set(PRIMARY_FLIGHT_DISPLAY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/src/primary_flight_display_view.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/src/primary_flight_display_model.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/scene/include
	${CMAKE_CURRENT_SOURCE_DIR}/view/include
        ${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/include
	${CMAKE_CURRENT_SOURCE_DIR}/indicators/graphics_layout_item/include
        ${CMAKE_CURRENT_SOURCE_DIR}/indicators/airspeed_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/indicators/attitude_indicator/include
	${CMAKE_CURRENT_SOURCE_DIR}/indicators/include
	#${CMAKE_CURRENT_SOURCE_DIR}/window/include
	#${CMAKE_CURRENT_SOURCE_DIR}/imu/include
        #${CMAKE_CURRENT_SOURCE_DIR}/imu/interface
)

    set(INERTIAL_MEASUREMENT_UNIT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/imu/src/imu_model.cpp
	)

    set(LEVEL_INDICATOR_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/indicators/src/linear_gauge.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/indicators/src/linear_gauge_value.cpp
	)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/scene/src/graphics_scene.cpp
	#${CMAKE_CURRENT_SOURCE_DIR}/indicators/src/indicator.cpp
	${LEVEL_INDICATOR_SOURCES}
	${AIRSPEED_INDICATOR_SOURCES}
	${ATTITUDE_INDICATOR_SOURCES}
	${PRIMARY_FLIGHT_DISPLAY_SOURCES}
)

#add_library(hudindicator SHARED
#    ${CMAKE_CURRENT_SOURCE_DIR}/types.h

#    ${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/src/indicator_view.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/src/indicator_model.cpp
#)

#target_include_directories(hudindicator
#    PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/includes
#)
#
#target_link_libraries(hudindicator PRIVATE Qt5::Widgets)
#
#set_target_properties(hudindicator
#    PROPERTIES
#        LINKER_LANGUAGE     CXX
#        LINK_WHAT_YOU_USE   TRUE
#)
#
#install(TARGETS hudindicator EXPORT pfdTargets
#    LIBRARY    DESTINATION   lib
#    ARCHIVE    DESTINATION   lib
#    RUNTIME    DESTINATION   bin
#    INCLUDES   DESTINATION   include
#)

#install(EXPORT pfdTargets
#    FILE          pfdTargets.cmake
#    NAMESPACE     pfd::
#    DESTINATION   lib/cmake/pfd
#)
