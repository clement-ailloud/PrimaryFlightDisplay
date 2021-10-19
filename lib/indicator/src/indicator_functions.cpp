/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "indicator/indicator_functions.h"

#include "math/functions.h"

#include "namespace.h"

#include "qfontmetrics.h"
#include "qpainter.h"
#include "qpen.h"
#include "qrect.h"
#include "qstring.h"

#include "qdebug.h"

#include <cmath>

// namespace QtHelper::Painter
// {
//
void drawTick(QPainter& painter, const QRect& rect)
{
    painter.drawRect(rect);
}

void drawRoundedTick(QPainter& painter, const QRect& rect, float xRadius, float yRadius,
                     Qt::SizeMode mode)
{
    painter.drawRoundedRect(rect, xRadius, yRadius, mode);
}

void drawTick(QPainter& painter, const QRect& rect, const QBrush& brush)
{
    painter.fillRect(rect, brush);
}

void drawText(QPainter& painter, int x, int y, const QString& text, Qt::Alignment alignment)
{
    const auto width = textWidth(text, painter.font());
    const auto height = textHeight(painter.font());
    painter.drawText(x, y, width, height, alignment, text);
}

void drawLargeTickLabel(QPainter& painter, const QRect& rect, int number, Qt::Alignment alignment)
{
    painter.drawText(rect, alignment, QString::number(number));
}

void drawLargeTickLabel(QPainter& painter, const QRect& rect, const QString& text,
                        Qt::Alignment alignment)
{
    painter.drawText(rect, alignment, text);
}

void drawBorder(QPainter& painter, const QSize& size, int flags)
{
    auto pen = painter.pen();
    pen.setWidth(4);
    painter.setPen(pen);

    if (flags & BorderPosition::BorderLeft)
    {
        painter.drawLine(QPoint(2, 2), QPoint(2, size.height() - 2));
    }

    if (flags & BorderPosition::BorderRight)
    {
        painter.drawLine(QPoint(size.width() - 2, 2), QPoint(size.width() - 2, size.height() - 2));
    }

    if (flags & BorderPosition::BorderTop)
    {
        painter.drawLine(QPoint(2, 2), QPoint(size.width() - 2, 2));
    }

    if (flags & BorderPosition::BorderBottom)
    {
        painter.drawLine(QPoint(2, size.height() - 2), QPoint(size.width() - 2, size.height() - 2));
    }
}

void drawGround(QPainter& painter, const QRect& rect, const QBrush& brush)
{
    painter.fillRect(rect, brush);
}

// } // end namespace QtHelper::Painter

// namespace QtHelper::Numerics
// {
//

// Helper for initializing the string of the labels
// Range is computed depending on the value
void setTicksLabelValue(std::vector<int>& labels, float value, float interval, size_t count)
{
    assert(interval >= 0.f);

    if (labels.size() != count)
        labels.resize(count);

    // Base drawn values on current value and remove the rest depending on interval
    const auto offset = static_cast<int>(Common::Math::floor(value, interval));

    const auto first = (count / 2ul) * interval + offset;
    for (auto i = 0ul; i < count; ++i)
        labels[i] = first - interval * i;
}

void drawCardinalDirections(QPainter& painter, const std::vector<QString>& directions, size_t count)
{
}

void setCardinalDirections(std::vector<QString>& v, int interval)
{
    static const std::map<int, QString> cardinalPoints{ { 0, "N" },    { 45, "NE" }, { 90, "E" },
                                                        { 135, "SE" }, { 180, "S" }, { 225, "SW" },
                                                        { 270, "S" },  { 315, "NW" } };

    size_t count = 360 / interval;
    if (v.size() <= 0)
        v.resize(count);

    for (auto i = 0ul; i < count; ++i)
    {
        const auto it = cardinalPoints.find(i * interval);
        v[i] = (it != cardinalPoints.end()) ? (*it).second : QString::number(i * interval);
    }
}

int textWidth(const QString& text, const QFont& font)
{
    const QFontMetrics fm(font);
    return fm.horizontalAdvance(text); // + 1;
}

int textHeight(const QFont& font)
{
    const QFontMetrics fm(font);
    return fm.ascent();
}

QSize textSize(const QString& text, const QFont& font)
{
    return { textWidth(text, font), textHeight(font) };
}

QRect& adjusted(QRect& rect, const QString& text, const QFont& font)
{
    rect.setSize(textSize(text, font));
    return rect;
}

float tickPositionFromValue(float value, float interval, float tickInterval)
{
    const auto reminder = std::fmod(value, interval);
    return std::fmod(reminder * (tickInterval / interval), tickInterval);
}

// } // end namespace QtHelper
