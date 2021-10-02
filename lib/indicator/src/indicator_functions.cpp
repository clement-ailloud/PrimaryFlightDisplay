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

#include "qpainter.h"
#include "qstring.h"
#include "qrect.h"
#include "qfontmetrics.h"

#include <cmath>

// namespace QtHelper::Painter
// {
//
void drawTick(QPainter& painter, const QRect& rect)
{
    painter.drawRect(rect);
}

void drawTick(QPainter& painter, const QRect& rect, const QBrush& brush)
{
    painter.fillRect(rect, brush);
}

void drawText(QPainter& painter,
              int x,
              int y,
              const QString& text,
              Qt::Alignment alignment)
{
    const auto width = textWidth(text, painter.font());
    const auto height = textHeight(painter.font());
    painter.drawText(x, y, width, height, alignment, text);
}

void drawLargeTickLabel(QPainter& painter, const QRect& rect, int number, Qt::Alignment alignment)
{
    painter.drawText(rect, alignment, QString::number(number));
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
    return fm.height();
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
