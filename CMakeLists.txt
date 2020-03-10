cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(PrimaryFlightDisplay VERSION 1.0 LANGUAGES CXX)

# Add gcc colors
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
endif()

find_package(Qt5
    COMPONENTS
        Core      REQUIRED
        Widgets   REQUIRED
        Gui       REQUIRED
)

#include(CMakePackageConfigHelpers)

#write_basic_package_version_file("pfdConfigVersion.cmake"
#    VERSION ${pfd_VERSION}
#)

#install(FILES "pfdConfig.cmake" "PFDConfigVersion.cmake"
#    DESTINATION lib/cmake/pfd
#)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_options(${CMAKE_PROJECT_NAME}
	PUBLIC
	-Wall -Wextra -Wpedantic
    )
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_options(${CMAKE_PROJECT_NAME}
	PUBLIC
	-Wall -Wextra -Wpedantic -Werror
    )
endif()

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
	include
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
	Qt5::Widgets
	Qt5::Core
	Qt5::Gui
)

set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
	CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON

        LINKER_LANGUAGE     CXX
        LINK_WHAT_YOU_USE   TRUE
)

target_compile_features(${CMAKE_PROJECT_NAME}
    PRIVATE
	cxx_constexpr
	cxx_final
	cxx_attributes
	cxx_auto_type
	cxx_inheriting_constructors
	cxx_inline_namespaces
	cxx_lambdas
	cxx_lambda_init_captures
	cxx_noexcept
	cxx_nullptr
	cxx_override
	cxx_range_for
	cxx_rvalue_references
	cxx_sizeof_member
	cxx_static_assert
	cxx_template_template_parameters
)

add_subdirectory(src)
