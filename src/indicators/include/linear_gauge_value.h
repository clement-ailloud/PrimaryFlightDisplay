#ifndef __MEASURE_SCALE_VALUE_H
#define __MEASURE_SCALE_VALUE_H


#include "QGraphicsItem"
#include "QGraphicsLayoutItem"

#include "QRect"
#include "QFont"
#include "QPen"
#include "QBrush"


class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QKeyEvent;


class LinearGaugeValue : public QGraphicsItem, public QGraphicsLayoutItem
{
    public:

        LinearGaugeValue(QGraphicsItem* parent = nullptr,
			 QGraphicsLayoutItem* parentLayout = nullptr);

        virtual ~LinearGaugeValue();

        void setBoundingRect(const QRectF rect){
            m_boundingRect = rect;

            update();
        }

        void setValue(float value);

        float value() const;

        void setMirrored(bool enable);

        bool mirrored() const;

        void setBrush(QBrush& brush);

        QBrush& brush();

        QRectF boundingRect() const override;

	void setGeometry(const QRectF& geometry) override;

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                QWidget* widget) override;


    protected:

	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;


    private:


        float m_value;
        int m_valueY;

        QRectF m_textRectFixed;
        QRectF m_textRectMovable;

        QPen m_pen;

        QFont m_font;

        float m_pixelSize;

        QRectF m_textRect;

        QRectF m_boundingRect;

        QBrush m_brush;

        Qt::Orientation m_orientation;

	bool m_mirrored;
};


#endif
