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

#include "qfontmetrics.h"
#include "qpainter.h"
#include "qrect.h"
#include "qstring.h"

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

void initializeTicksLabelValue(std::vector<int>& v, float value, unsigned long count,
                               float interval)
{
}

void drawBorder(QPainter& painter, const QSize& size)
{
    const std::vector<QPoint> boundingPoints{ { 0, 0 },
                                              { size.width(), 0 },
                                              { size.width(), size.height() },
                                              { 0, size.height() } };

    painter.drawPolyline(boundingPoints.data(), boundingPoints.size());
}

void drawGround(QPainter& painter, const QRect& rect, const QBrush& brush)
{
    painter.fillRect(rect, brush);
}

// } // end namespace QtHelper::Painter

// namespace QtHelper::Numerics
// {
//
int textWidth(const QString& text, const QFont& font)
{
    const QFontMetrics fm(font);
    return fm.horizontalAdvance(text) + 1;
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

// } // end namespace QtHelper
