#ifndef __MEASURE_SCALE_VALUE_H
#define __MEASURE_SCALE_VALUE_H

#include "QWidget"

#include "QBrush"
#include "QFont"
#include "QPen"
#include "QRect"

class QPainter;
class QWidget;
class QKeyEvent;

class LinearGaugeValue : public QWidget
{
public:
    LinearGaugeValue(QWidget* parent = nullptr);

    virtual ~LinearGaugeValue();

    float value() const;
    void setValue(float value);

    bool mirrored() const;
    void setMirrored(bool enable);

    QBrush& brush();
    void setBrush(QBrush& brush);

    void paintEvent(QPaintEvent* event) override;

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
