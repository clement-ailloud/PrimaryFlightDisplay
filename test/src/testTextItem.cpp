/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "text_item/text_item.h"

#include "gtest/gtest.h"

using namespace testing;

TEST(TestTextItem, test_TextItem)
{
    // Default constructor
    {
        TextItem item;
        EXPECT_EQ(item.text(), QString());
        EXPECT_EQ(item.font(), QFont());
        EXPECT_EQ(item.position(), QPoint());
        EXPECT_EQ(item.width(), 0);
        EXPECT_EQ(item.height(), 0);
    }

    // Custom constructor using default font
//    {
//        QString text("Hello world!");
//        TextItem item(text);
//        EXPECT_EQ(item.text(), text);
//        EXPECT_EQ(item.font(), QFont());
//    }

//    // Custom constructor
//    {
//        TextItem item("Hello world!", QFont("Calibri"));
//        EXPECT_EQ(item.text(), "Hello world!");
//        EXPECT_EQ(item.font(), QFont("Calibri"));
//    }
}

//TEST(TestTextItem, setFont)
//{
//    TextItem item("Hello world!");
//    auto width = item.width();
//    auto height = item.height();
//
//    item.setFont(QFont("Calibri"));
//    EXPECT_EQ(item.position(), QPoint());
//    EXPECT_NE(item.width(), width);
//    EXPECT_NE(item.height(), height);
//}

int main(int argc, char* argv[])
{
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
