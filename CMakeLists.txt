cmake_minimum_required(VERSION 3.17.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
#include(CCache)

project(PrimaryFlightDisplay
    VERSION 1.0
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/clement-ailloud/PrimaryFlightDisplay.git
)

#include(CPackConfig)
include(PreCommit)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
#set(CMAKE_CXX_CPPCHECK cppcheck --project=${CMAKE_BINARY_DIR}/compile_commands.json --enable=all --output-file=${CMAKE_BINARY_DIR}/cppcheck_output.txt)
#set(CMAKE_CXX_CLANG_TIDY clang-tidy --use-color -header-filter=.* --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy -p ${CMAKE_BINARY_DIR})
set(CMAKE_LINK_WHAT_YOU_USE iwyu ${CMAKE_BINARY_DIR})
#set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE )

# Common output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<LOWER_CASE:$<CONFIG>>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<LOWER_CASE:$<CONFIG>>)

# Ninja Multi-Config
if(CMAKE_GENERATOR STREQUAL "Ninja Multi-Config")
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

# Common compile options
if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        $<$<CONFIG:Release>:-Werror>
        -fdiagnostics-color=always
        $<$<CONFIG:Debug>:-fprofile-instr-generate>
        $<$<CONFIG:Debug>:-fcoverage-mapping>
    )
endif()

if (CMAKE_PLATFORM_ID STREQUAL "Linux")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif()

#include(ExternalProject)
#ExternalProject_Add(
#    VirtualJoystickController
#    #PREFIX ${CMAKE_CURRENT_BINARY_DIR}/VirtualJoystickController
#    GIT_REPOSITORY https://github.com/clement-ailloud/VirtualJoystickController
#    GIT_TAG develop
#    TIMEOUT 10
#    #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#    UPDATE_COMMAND ""
#    INSTALL_COMMAND ""
#    #LOG_DOWNLOAD ON
#    #CONFIGURE_COMMAND ""
#    #BUILD_COMMAND ""
#    #LOG_CONFIGURE ON
#    #LOG_BUILD ON
#    #BUILD_IN_SOURCE TRUE
#)

#find_package(Boost 1.6.1 REQUIRED)
#find_package(Git REQUIRED)
find_package(Qt5
    COMPONENTS
        Core      REQUIRED
        Widgets   REQUIRED
        Gui       REQUIRED
)

add_executable(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primary_flight_display/src/primary_flight_display_view.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        #${Boost_LIBRARIES}
        PrimaryFlightDisplayIndicator
	Qt5::Widgets
)


set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
        #DEBUG_POSTFIX "-debug"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<LOWER_CASE:$<CONFIG>>

	CXX_STANDARD 17
        CXX_EXTENSIONS ON
        CXX_STANDARD_REQUIRED ON

        LINKER_LANGUAGE     CXX
)

install(TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    CONFIGURATIONS Debug Release
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

add_subdirectory(lib)
add_subdirectory(text_item)
add_subdirectory(widgets)
add_subdirectory(primary_flight_display)

list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")
include(CTest)
add_subdirectory(test)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "1.0.0")
#set(CPACK_PACKAGE_CONTACT "your_email@example.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "${CMAKE_PROJECT_NAME} is an interface that displays the flight instrument")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Clement Ailloud")
include(CPack)
