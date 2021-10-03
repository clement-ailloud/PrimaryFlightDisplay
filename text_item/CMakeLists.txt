
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

install(TARGETS TextItem
    EXPORT TextItemTargets
        CONFIGURATIONS Debug Release
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
