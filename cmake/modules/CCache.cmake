include_guard(GLOBAL)

set(CCACHE_FOUND FALSE)
if(NOT(CCACHE_EXECUTABLE))
    find_program(CCACHE_COMMAND ccache NO_CACHE REQUIRED)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_COMMAND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_COMMAND}")

    execute_process (
        COMMAND bash -c "command -v ccache"
        OUTPUT_VARIABLE CCACHE_PATH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process (
        COMMAND bash -c "ccache --version | head -n 1 | awk '{print $3}'"
        OUTPUT_VARIABLE CCACHE_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(CCACHE_FOUND TRUE)
    set(CCACHE_EXECUTABLE ${CCACHE_COMMAND} CACHE FILEPATH "CCache command line")
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
    set(ENV{CCACHE_DIR} ${CMAKE_SOURCE_DIR}/.cache/ccache)
    #message(STATUS "Found CCache: ${CCACHE_PATH} (found version: \"${CCACHE_VERSION}\")")
endif()
