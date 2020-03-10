#include "graphics_view.h"

#include "qwidget.h"

#include "QGraphicsItem"

#include <iostream>



GraphicsView::GraphicsView(QWidget *parent)
{
}


GraphicsView::GraphicsView(QGraphicsScene* scene, QWidget* parent)
{

//    if (scene)
//    {
//        const auto itemList = scene->items();
//
//        for (auto item = itemList.begin(); item != itemList.end(); ++item)
//        {
////            QPainter painter(*item);
////
////            (*item)->paint(&painter, nullptr, nullptr);
//
//            (*item)->repaint();
//        }
//    }
}


GraphicsView::~GraphicsView()
{
}


void GraphicsView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}
