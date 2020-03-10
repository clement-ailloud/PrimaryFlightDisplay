/*
 * @file	main.cpp
 *
 * @brief
 *
 * @date
 *
 * @author	Clement Ailloud
 */



#include "qapplication.h"

#include "graphics_scene.h"
//#include "QGraphicsScene"
#include "QGraphicsView"
#include "QOpenGLWidget"
#include "QSurfaceFormat"
#include "qrect.h"

#include <memory>

#include "primary_flight_display_view.h"



/*
 * @fn		main
 *
 * @brief	main    function description
 *
 * @param	argc	arguments count
 *
 * @param	argv	arguments vector
 */

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GraphicsScene scene;

    std::unique_ptr<View::PrimaryFlightDisplay> pfd = std::make_unique<View::PrimaryFlightDisplay>();
    scene.addItem(pfd.get());

    QGraphicsView view(&scene);
    view.setRenderHints(QPainter::Antialiasing);
//    view.centerOn(view.mapToScene(view.viewport()->rect().bottomLeft()));
//    view.translate(600, 600);
    view.resize(300, 600);
    view.showMaximized();

    return app.exec();
}
