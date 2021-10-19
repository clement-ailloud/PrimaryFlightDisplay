cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

project(PrimaryFlightDisplay
    VERSION 1.0
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/clement-ailloud/PrimaryFlightDisplay.git
)

include(CPackConfig)
include(PreCommit)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_LINK_WHAT_YOU_USE iwyu ${CMAKE_BINARY_DIR})
#set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE )

# Ninja Multi-Config
get_property(IS_MULTI_CONFIG_GENERATOR GLOBAL
    PROPERTY GENERATOR_IS_MULTI_CONFIG
)
if(IS_MULTI_CONFIG_GENERATOR)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE Release)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})
endif()

# Common compile options
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    add_compile_options(
        -g
        -Wall
        -Wextra
        -Wpedantic
        -fdiagnostics-color=always
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-fprofile-instr-generate>
        $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-fcoverage-mapping>
    )
endif()

if(CMAKE_PLATFORM_ID STREQUAL "Linux")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif()

set(CMAKE_TLS_VERIFY TRUE)

#find_package(Git REQUIRED)
include(ExternalProject)
ExternalProject_Add(VirtualJoystickControllerProject
    PREFIX external/VirtualJoystickController
    GIT_REPOSITORY https://github.com/clement-ailloud/VirtualJoystickController
    GIT_TAG develop
    TIMEOUT 10
    UPDATE_COMMAND ""#${GIT_EXECUTABLE} pull"
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/external/VirtualJoystickController/src/VirtualJoystickControllerProject-build/Debug/libVirtualJoystickController.so
)
add_library(VirtualJoystickController SHARED IMPORTED)

target_include_directories(VirtualJoystickController
    INTERFACE
        ${CMAKE_BINARY_DIR}/external/VirtualJoystickController/src/VirtualJoystickControllerProject/include
)

ExternalProject_Get_Property(VirtualJoystickControllerProject BINARY_DIR)
set_property(TARGET VirtualJoystickController
    PROPERTY
        IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/${BINARY_DIR}/Debug/libVirtualJoystickController.so
)

file(COPY_FILE "${BINARY_DIR}/Debug/libVirtualJoystickController.so" "${CMAKE_BINARY_DIR}/${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG}/libVirtualJoystickController.so")

find_package(Qt5
    COMPONENTS
        Core      REQUIRED
        Widgets   REQUIRED
        Gui       REQUIRED
)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOGEN_PARALLEL TRUE)

add_executable(${CMAKE_PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

if(ANDROID)
    target_sources(${CMAKE_PROJECT_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/android/AndroidManifest.xml
    )
endif()

add_dependencies(${CMAKE_PROJECT_NAME} VirtualJoystickControllerProject)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        VirtualJoystickController
        FlightInstruments
	Qt5::Widgets
)

set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
        #DEBUG_POSTFIX "-debug"

	CXX_STANDARD 17
        CXX_EXTENSIONS ON
)

install(TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES}
    PUBLIC_HEADER DESTINATION include
)

add_subdirectory(primary_flight_display)
add_subdirectory(lib)
add_subdirectory(text_item)
add_subdirectory(widgets)

if(NOT ANDROID)
    list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")
    include(CTest)
    add_subdirectory(test)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test PROPERTY PROCESSOR_AFFINITY TRUE)
endif()


#include(CMakePackageConfigHelpers)

#write_basic_package_version_file("pfdConfigVersion.cmake"
#    VERSION ${pfd_VERSION}
#)

#install(FILES "pfdConfig.cmake" "PFDConfigVersion.cmake"
#    DESTINATION lib/cmake/pfd
#)
