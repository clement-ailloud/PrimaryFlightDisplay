#ifndef __WINDOW_H
#define __WINDOW_H


#include "qgraphicswidget.h"


class Window : public QGraphicsWidget
{
    public:

        Window(QGraphicsWidget* parent = nullptr);

        ~Window();
};


#endif // WINDOW_H
