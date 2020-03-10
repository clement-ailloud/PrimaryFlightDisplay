#include "graphics_scene.h"


GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent)
{
}


GraphicsScene::GraphicsScene(const QRectF& sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{
}


GraphicsScene::~GraphicsScene()
{
}
