/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "indicator/indicator_functions.h"

#include "gtest/gtest.h"

#include "QGuiApplication"
#include "QThread"
#include "QTimer"
#include "qsize.h"

#include <vector>

#define EXPECT_CONTAINER_EQ(lhs, rhs)                                                              \
    ASSERT_EQ(lhs.size(), rhs.size());                                                             \
    for (auto i = 0ul; i < lhs.size(); ++i)                                                        \
        EXPECT_EQ(lhs[i], rhs[i]);

using namespace testing;

TEST(TestIndicatorFunctions, test_textWidth)
{
    EXPECT_EQ(textWidth(""), 0);
    // EXPECT_EQ(textWidth("Hello"), 0);
    // EXPECT_EQ(textWidth("world"), 0);
    // EXPECT_EQ(textWidth("Hello world"), 0);
}

TEST(TestIndicatorFunctions, test_textHeight)
{
    int argc{ 0 };
    char** argv{ nullptr };
    QGuiApplication app(argc, argv);

    // const QFont font("Cantarell", 16, QFont::Bold);
    // EXPECT_EQ(textHeight(font), 16);
    // EXPECT_EQ(textHeight(font), 16);

    QTimer::singleShot(10000, &app,
                       []()
                       {
                           qApp->processEvents();
                           qApp->quit();
                       });

    app.processEvents();
    app.exec();
    app.thread()->wait();
}

TEST(TestIndicatorFunctions, test_getStepSpan)
{
    {
        const auto count = 0ul;
        const QSize size(0.f, 0.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Vertical), 0.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Horizontal), 0.f);
    }
    {
        const auto count = 1ul;
        const QSize size(10.f, 10.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Vertical), 10.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Horizontal), 10.f);
    }
    {
        const auto count = 2ul;
        const QSize size(10.f, 10.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Vertical), 5.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Horizontal), 5.f);
    }
    {
        const auto count = 2ul;
        const QSize size(5.f, 10.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Vertical), 5.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Horizontal), 2.5f);
    }
    {
        const auto count = 2ul;
        const QSize size(5.f, 15.f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Vertical), 7.5f);
        EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Horizontal), 2.5f);
    }
    // {
    //     const auto count = 3ul;
    //     const QSizeF size(20.f, 20.f);
    //     EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Vertical), 6.6666f);
    //     EXPECT_FLOAT_EQ(getStepSpan<float>(size, count, Qt::Horizontal), 6.6666f);
    // }
}

TEST(TestIndicatorFunctions, test_tickPositionFromValue)
{
    EXPECT_FLOAT_EQ(tickPositionFromValue(0.f, 10.f, 100.f), 0.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(1.f, 10.f, 100.f), 10.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(5.f, 10.f, 100.f), 50.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(10.f, 10.f, 100.f), 0.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(11.f, 10.f, 100.f), 10.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(15.f, 10.f, 100.f), 50.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(100.f, 10.f, 100.f), 0.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(101.f, 10.f, 100.f), 10.f);
    EXPECT_FLOAT_EQ(tickPositionFromValue(111.f, 10.f, 100.f), 10.f);
}

TEST(TestIndicatorFunctions, test_updateTicksLabelValue)
{
    // Dummy case
    {
        std::vector<int> labels;
        EXPECT_DEATH(updateTicksLabelValue(labels, 0, 0, 0), "");
    }
    // Dummy case
    {
        std::vector<int> labels;
        EXPECT_DEATH(updateTicksLabelValue(labels, 0, -1, 0), "");
    }
    // Dummy case
    {
        std::vector<int> labels;
        updateTicksLabelValue(labels, 0, 1, 0);

        std::vector<int> expected;
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    {
        std::vector<int> labels(3, 0);
        updateTicksLabelValue(labels, 0, 10, 3);

        std::vector<int> expected{ 10, 0, -10 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    // Value close to interval
    {
        std::vector<int> labels(3, 0);
        updateTicksLabelValue(labels, 9, 10, 3);

        std::vector<int> expected{ 10, 0, -10 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    // Value equal to interval
    {
        std::vector<int> labels(3, 0);
        updateTicksLabelValue(labels, 10, 10, 3);

        std::vector<int> expected{ 20, 10, 0 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
    // Value exceeds interval
    {
        std::vector<int> labels(3, 0);
        updateTicksLabelValue(labels, 11, 10, 3);

        std::vector<int> expected{ 20, 10, 0 };
        EXPECT_CONTAINER_EQ(labels, expected);
    }
}

TEST(TestIndicatorFunctions, test_getMiddleTickPadding)
{
    EXPECT_EQ(getMiddleTickPadding({ 1, 1 }, 5, Qt::Vertical), 6);
    EXPECT_EQ(getMiddleTickPadding({ 10, 5 }, 10, Qt::Vertical), 20);

    EXPECT_EQ(getMiddleTickPadding({ 1, 1 }, 5, Qt::Horizontal), 5);
    EXPECT_EQ(getMiddleTickPadding({ 10, 5 }, 10, Qt::Horizontal), 12);
}

int main(int argc, char* argv[])
{
    InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
