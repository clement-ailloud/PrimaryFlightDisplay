#include "window.h"

#include "primary_flight_display.h"

#include "qgraphicslayout.h"
#include "qgraphicslinearlayout.h"
#include "qgraphicslayoutitem.h"
#include "qgraphicsgridlayout.h"


Window::Window(QGraphicsWidget* parent)
    : QGraphicsWidget(parent, Qt::Window)
{
//    PrimaryFlightDisplay pfd();
//
//    QGraphicsGridLayout* windowLayout = new QGraphicsGridLayout();
//
//    windowLayout->addItem(&pfd, 0, 0);
//
//    setLayout(windowLayout);
}


Window::~Window()
{
}
