
//!
//! \file       movable_linear_gauge_value.cpp
//!
//! \brief      GUI handling indicator value
//!
//! \date
//!
//! \author     Clement Ailloud
//!

#include "linear_gauge_value.h"

#include "QFontMetrics"
#include "QKeyEvent"
#include "QPainter"
#include "QPoint"
#include "QString"

#include <cmath>
#include <iostream>
#include <vector>

LinearGaugeValue::LinearGaugeValue(QWidget* parent)
    : QWidget(parent)
    // Pixel size for computing bounding rectangle
    , m_value(0.f)
    , m_valueY(0)
    , m_boundingRect(QRect())
    , m_orientation(Qt::Horizontal)
    , m_mirrored(false)
    , m_pen = QPen(Qt::NoBrush, 3.f)
    , m_brush("white")
{
    m_font.setPixelSize(26);
    m_font.setBold(true);

    m_pixelSize = static_cast<float>(m_font.pixelSize());

    QFontMetrics fm(m_font);

    // Get rectangle to fit the text
    m_textRect = fm.boundingRect("000");
    m_textRect.adjust(0, 0, -m_pen.width(), -m_pen.width());
    m_textRect.setWidth(m_textRect.width() + 10);

    m_boundingRect = m_textRect;

    // Get rectangle area of two digit
    m_textRectFixed = fm.boundingRect("00");
    m_textRectFixed.adjust(0, 0, m_pen.width() * 2, -m_pen.width());

    // Get rectangle to fit one digit
    m_textRectMovable = fm.boundingRect("0");
    m_textRectMovable.adjust(0, 0, m_pen.width() * 2, -m_pen.width());

    m_boundingRect.setRight(static_cast<float>(m_boundingRect.topRight().x()) * 1.25);
    m_boundingRect.moveCenter(QPoint(0, 0));

    // TODO: Replace by polygon rotation
    switch (m_orientation)
    {
    case Qt::Horizontal:

        m_textRect.moveTopLeft(m_boundingRect.topLeft());

        m_textRectFixed.moveTopLeft(m_textRect.topLeft());

        m_textRectMovable.moveTopLeft(m_textRectFixed.topRight());

        break;

    case Qt::Vertical:

    default:
        break;
    }
}

LinearGaugeValue::~LinearGaugeValue() = default;

float LinearGaugeValue::value() const
{
    return m_value;
}

void LinearGaugeValue::setValue(float value)
{
    m_value = value;
}

bool LinearGaugeValue::mirrored() const
{
    return m_mirrored;
}

void LinearGaugeValue::setMirrored(bool enable)
{
    m_mirrored = enable;
}

QBrush& LinearGaugeValue::brush()
{
    return m_brush;
}

void LinearGaugeValue::setBrush(QBrush& brush)
{
    m_brush = brush;
}

void LinearGaugeValue::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    painter->setFont(m_font);
    painter->setBrush(QColor("white"));

    if (m_mirrored)
    {
        painter->scale(-1.0, 1.0);
    }

    // Clip area
    painter->setClipRect(m_boundingRect);

    // painter->drawRect(m_boundingRect);
    // painter->drawRect(m_textRect);

    // Create a polygon fitting along with the text area
    const std::array<QPointF, 7> container = {
        m_boundingRect.topLeft(),
        QPointF(m_textRect.topRight().x() + 1, m_textRect.top()),
        QPointF(m_textRect.topRight().x() + 1, m_textRect.top() * .5),
        QPointF(m_boundingRect.right(), 0),
        QPointF(m_textRect.bottomRight().x() + 1, m_textRect.bottomRight().y() * .5),
        QPointF(m_textRect.bottomRight().x() + 1, m_textRect.bottomRight().y()),
        m_textRect.bottomLeft()
    };

    // m_pen.setColor(QColor("#7ec850"));
    m_pen.setColor(QColor("#aa32cd32"));

    painter->setPen(m_pen);

    // Draw value container
    painter->drawPolygon(container.data(), container.size());

    // Dissociate decimal from the whole part of value
    auto whole = 0.f;
    const auto decimal = std::modf(m_value, &whole);

    // Get whole from value
    QString number = QString::number(whole);

    // Remove last digit
    number.chop(1);

    m_pen.setColor(QColor("#7ec850"));
    painter->setPen(m_pen);

    // Draw value except the removed last digit
    painter->drawText(QRectF(m_textRectFixed), Qt::AlignRight, QString(number));

    std::vector<int> numbers;

    // Fill elements with the whole part of the current plus next value
    for (auto i = whole + 1; i >= whole; --i)
    {
        numbers.push_back(std::fmod(i, 10.f));
    }

    auto j = 0;
    const auto start = m_textRect.top() - 1;
    const auto stop = m_textRect.bottom() - 1;

    // Offset text value
    const auto offset = static_cast<int>(std::fmod(decimal * m_pixelSize, m_pixelSize) + .5f);

    // Draw value
    for (auto i = start; i <= stop; i += m_pixelSize)
    {
        auto y = i + offset + 1;

        // Draw last digit
        painter->drawText(m_textRectMovable.x(), y, QString::number(numbers[j]));

        j++; // Draw next value
    }
}
