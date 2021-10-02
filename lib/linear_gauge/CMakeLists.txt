
add_library(LinearGauge
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linear_gauge.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/src/linear_gauge_value.cpp
)

target_include_directories(LinearGauge
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/private
)

target_link_libraries(LinearGauge
    PRIVATE
        IndicatorFunctions
        Common
        TextItem
	Qt5::Core
        Qt5::Widgets
)

set_target_properties(LinearGauge
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>

	CXX_STANDARD 17
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON

        LINKER_LANGUAGE     CXX
        #LINK_WHAT_YOU_USE   TRUE
)

install(TARGETS LinearGauge
    EXPORT TextItemTargets
        CONFIGURATIONS Debug Release
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
