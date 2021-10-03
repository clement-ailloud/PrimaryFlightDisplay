
add_library(GaugeIndicator
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gauge_indicator/private/linear_gauge_private.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linear_gauge_private.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gauge_indicator/abstract_gauge.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/abstract_gauge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linear_gauge.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/src/linear_gauge_value.cpp
)

target_include_directories(GaugeIndicator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GaugeIndicator
    PRIVATE
        Common
        IndicatorFunctions
	Qt5::Core
        Qt5::Widgets
)

set_target_properties(GaugeIndicator
    PROPERTIES
	CXX_STANDARD 17
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON
)

install(TARGETS GaugeIndicator EXPORT GaugeIndicatorTargets
    CONFIGURATIONS Debug Release
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
