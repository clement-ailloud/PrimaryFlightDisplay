


#include "QGraphicsView"


class GraphicsView : public QGraphicsView
{
    public:

        GraphicsView(QWidget *parent = nullptr);

        GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

        virtual ~GraphicsView();


    protected:

        void wheelEvent(QWheelEvent *event) override;
};
