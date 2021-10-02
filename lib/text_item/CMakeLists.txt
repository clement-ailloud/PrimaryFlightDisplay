
add_library(TextItem
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/src/text_item.cpp
)

target_include_directories(TextItem
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(TextItem
    PRIVATE
        IndicatorFunctions
	Qt5::Core
	Qt5::Gui
)

#set_target_properties(TextItem
#    PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test/$<CONFIG>
#
#	CXX_STANDARD 17
#        CXX_EXTENSIONS ON
#        CXX_STANDARD_REQUIRED ON
#
#        LINKER_LANGUAGE     CXX
#)

install(TARGETS TextItem
    EXPORT TextItemTargets
        CONFIGURATIONS Debug Release
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
