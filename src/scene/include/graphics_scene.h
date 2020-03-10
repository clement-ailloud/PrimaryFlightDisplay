/*
 * @file	graphics_scene.h
 *
 * @brief	airspeed_indicator_view file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */



#include "QGraphicsScene"


class GraphicsScene : public QGraphicsScene
{
    public:

        GraphicsScene(QObject* parent = nullptr);
	GraphicsScene(const QRectF& sceneRect, QObject *parent = nullptr);
	GraphicsScene(const GraphicsScene&) = delete;
	GraphicsScene(GraphicsScene&&) = delete;

        virtual ~GraphicsScene();

	GraphicsScene& operator=(const GraphicsScene&) = delete;
	GraphicsScene& operator=(GraphicsScene&) = delete;
};
