
add_library(IndicatorFunctions
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/indicator_functions.cpp
)

target_include_directories(IndicatorFunctions
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(IndicatorFunctions
    PRIVATE
	Qt5::Core
	Qt5::Gui
)

#set_target_properties(IndicatorFunctions
#    PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test/$<CONFIG>
#
#	CXX_STANDARD 17
#        CXX_EXTENSIONS ON
#        CXX_STANDARD_REQUIRED ON
#)

install(TARGETS IndicatorFunctions
    EXPORT IndicatorFunctionsTargets
        CONFIGURATIONS Debug Release
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
