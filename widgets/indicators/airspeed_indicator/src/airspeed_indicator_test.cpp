
//!
//! \file	airspeed_indicator_test.cpp
//!
//! \brief	airspeed_indicator_test file description
//!
//! \date
//!
//! \author	Clement Ailloud
//!
//!

#include <memory>

#include "qapplication.h"

#include "QGraphicsLinearLayout"

#include "graphics_scene.h"
#include "graphics_view.h"

#include "airspeed_indicator.h"
#include "airspeed_indicator_model.h"
#include "airspeed_indicator_view.h"

#include "qtimer.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // std::unique_ptr<View::AirspeedIndicator> indicatorView =
    // make_unique<View::AirspeedIndicator>();
    View::AirspeedIndicator* indicatorView = new View::AirspeedIndicator();

    // std::unique_ptr<Model::AirspeedIndicator> indicatorModel =
    // make_unique<Model::AirspeedIndicator>();
    Model::AirspeedIndicator* indicatorModel = new Model::AirspeedIndicator();

    AirspeedIndicator airspeedIndicator(indicatorView, indicatorModel);

    // QPainter painter;

    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical);

    if (!layout)
    {
        auto i = 0;
    }

    QGraphicsScene scene;
    // scene.render(&painter);

    // scene.addItem(indicatorView->graphicsItem());

    QGraphicsView view(&scene);
    view.resize(300, 600);

    // Enable OpenGL rendering
    // view.setViewport(new QOpenGLWidget(QGLFormat(QGL::SampleBuffers)));

    // view.setRenderHints(QPainter::Antialiasing);
    // view.setAttribute(Qt::WA_TranslucentBackground);
    // view.setAttribute(Qt::FramelessWindowHint);
    // view.viewport()->setAutoFillBackground(false);

    view.show();

    return app.exec();
}
