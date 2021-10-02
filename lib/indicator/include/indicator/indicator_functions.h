/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "qfont.h"
#include "Qt"

class QBrush;
class QFont;
class QRect;
class QPainter;
class QSize;
class QString;

/**
 * @brief   Draws large tick depending on the given rectangle.
 *
 * The rectangle refers to the position and size of the tick.
 */
void drawTick(QPainter& painter, const QRect& rect);

void drawTick(QPainter& painter, const QRect& rect, const QBrush& brush);

void drawText(QPainter& painter,
              int x,
              int y,
              const QString& text,
              Qt::Alignment alignment = Qt::AlignVCenter | Qt::AlignLeft);

/**
 * @brief   Draws value that is associated to the large tick depending on the given rectangle.
 *
 * The rectangle refers to the position and size of the tick value.
 */
void drawLargeTickLabel(QPainter& painter,
                        const QRect& rect,
                        int number = 0,
                        Qt::Alignment alignment = Qt::AlignLeft);

/**
 * @brief   Returns the width in pixel depending on font
 * @param   text
 * @param   font
 */
int textWidth(const QString& text, const QFont& font);

/**
 * @brief   Returns the height in pixel depending on font
 * @param   font
 */
int textHeight(const QFont& font);

/**
 * @brief   Returns the size surrounding a string depending on font
 * @param   text
 * @param   font
 */
QSize textSize(const QString& text, const QFont& font);

/**
 * @brief   Returns the rectangle surrounding a string depending on font
 * @param   rectangle
 * @param   text
 * @param   font for the text
 */
QRect& adjusted(QRect& rect, const QString& text, const QFont& font);
