
//!
//! \file	movable_linear_gauge.h
//!
//! \brief	movable_linear_gauge.h file description
//!
//! \date
//!
//! \author	Clement Ailloud
//!



#ifndef __MEASURE_SCALE_H
#define __MEASURE_SCALE_H


#include "qgraphicsitem.h"
#include "QGraphicsLayoutItem"

#include "qfont.h"
#include "qcolor.h"

#include <memory>


class QColor;
class QFont;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QSizeF;
class QRect;
class QRectF;
class LinearGaugeValue;


class LinearGauge final : public QGraphicsItem, public QGraphicsLayoutItem
{
    public:

        LinearGauge(QGraphicsItem* parent = nullptr, QGraphicsLayoutItem* parentLayout = nullptr);

        LinearGauge(const LinearGauge&) = default;
	LinearGauge(LinearGauge&&) = default;

        virtual ~LinearGauge();

        void setValue(float value);

        float value() const;

        void reset();

//        void setOrientation(Qt::Orientation) const;

        void setTextVisible(bool visible);

        bool textVisible() const;

        void drawBoundingRect(QPainter* painter) const;

//        void setFillBrush(const QBrush& brush);
//
//        QBrush fillBrush() const;
//
//        void setLevelBrush(const QBrush& brush);
//
//        QBrush levelBrush() const;

        QRectF boundingRect() const override;

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                QWidget* widget) override;

//        void keyPressEvent(QKeyEvent *event) override;

        void drawCurrentSpeed(QPainter* painter, int speed);

	void setGeometry(const QRectF& geometry) override;

        void setBorder(bool enable);

        int valueToDraw(float value, int step) const;

        enum Alignment
        {
            AlignLeft,
            AlignRight,
            AlignCenter
        };

        void setAlignment(Alignment alignment);

        void drawGround(QPainter* painter, const QRect &rect, const QBrush& brush);

	// Assignement operators
	LinearGauge& operator =(const LinearGauge&) = default;
	LinearGauge& operator =(LinearGauge&&) = default;

	//        void valueChanged(int value) const;


    protected:

	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;


    private:

	void init();

	float m_value;

	int m_scaleLength;

        int m_textAlignment;

        QRect m_textRect;
        QRect m_largeTickRect;
        QRect m_middleTickRect;

	int m_largeTick;
	int m_mediumTick;
	int m_smallTick;

	int m_largeTickInterval;
	int m_largeTickHeight;
	int m_middleTickHeight;

	Alignment m_aligment;

	bool m_textVisible;

        //int m_valueY;
        int m_stepValue;

	bool m_drawBorder;

	QRectF m_boundingRect;

        int m_tick;

        int m_interval;

        int m_yStart;
        int m_yStop;

	int m_textHeight;

        QFont m_font;
        QFont m_fontCurrentSpeed;

        QColor m_tickFillColor;
        QColor m_tickBorderColor;

        int m_drawOffsetValue;
        int m_drawStartY, m_drawStopY;

        int m_borderTop, m_borderBot;

        int m_x1, m_x2, m_x11, m_x22, m_x111, m_x222;

        int m_penWidth;
        int m_rectHeight;
        int m_drawRectHeight;
};

#endif
