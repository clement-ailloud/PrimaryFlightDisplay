find_package(GTest REQUIRED)

list(APPEND CMAKE_CTEST_ARGUMENTS "--verbose")

# Test TextItem
add_executable(testTextItem
    ${CMAKE_CURRENT_SOURCE_DIR}/src/testTextItem.cpp
)

target_link_libraries(testTextItem
    PRIVATE
        TextItem
	Qt5::Gui
	Qt5::Core
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME TestTextItem
    COMMAND testTextItem
    --config $<CONFIG>
    --exe $<TARGET_FILE:testTextItem>
)

# Test indicator's functions
add_executable(testIndicatorFunctions
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_indicator_functions.cpp
)

target_link_libraries(testIndicatorFunctions
    PRIVATE
        IndicatorFunctions
        Qt5::Gui
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME TestIndicatorFunctions
    COMMAND testIndicatorFunctions
    --config $<CONFIG>
    --exe $<TARGET_FILE:testIndicatorFunctions>
)

add_executable(testLinearGauge
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_linear_gauge.cpp
)

target_include_directories(testLinearGauge
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(testLinearGauge
    PRIVATE
        IndicatorFunctions
        Qt5::Gui
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME TestLinearGauge
    COMMAND testLinearGauge
    --config $<CONFIG>
    --exe $<TARGET_FILE:testLinearGauge>
)
