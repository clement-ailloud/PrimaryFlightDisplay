
add_library(Common
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/math/src/functions.cpp
)

target_include_directories(Common
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/math/include
)

set_target_properties(Common
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib/$<CONFIG>

	CXX_STANDARD 17
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON

        LINKER_LANGUAGE     CXX
        #LINK_WHAT_YOU_USE   TRUE
)

install(TARGETS Common
    EXPORT CommonTargets
        CONFIGURATIONS Debug Release
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)

#export(EXPORT CommonTargets NAMESPACE Common)
