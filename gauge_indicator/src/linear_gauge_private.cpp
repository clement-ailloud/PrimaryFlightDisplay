/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "gauge_indicator/private/linear_gauge_private.h"

#include "gauge_indicator/linear_gauge.h"

#include "qrect.h"
#include "qsize.h"

LinearGaugePrivate::LinearGaugePrivate(LinearGauge const* view)
    : m_view(view)
{
}

void LinearGaugePrivate::onSizeChanged(const QSize& size)
{
    // Put LinearGauge::resizeEvent code here
}

/**
 * @brief Skeleton for setting the position of a tick in screen coordinates.
 *
 * Move the position of the rectangle to the center of the screen so it eases the draw operation.
 * The only thing to do before drawing is to adjust the x or y position depending on the orientation
 * and the alignment.
 */
QRect& LinearGaugePrivate::getTickPosition(QRect& rect, int thickness, int padding)
{
    auto x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    // Set tick thickness depending on orientation
    switch (m_view->orientation())
    {
    case Qt::Horizontal:
    {
        x1 = m_view->width() / 2 - thickness;
        x2 = m_view->width() / 2 + thickness;
        break;
    }
    case Qt::Vertical:
    {
        y1 = m_view->height() / 2 - thickness;
        y2 = m_view->height() / 2 + thickness;
        break;
    }
    }

    // Set position depending on orientation and alignment
    switch (static_cast<int>(m_view->orientation()) | static_cast<int>(m_view->alignment()))
    {
    case Qt::Vertical | Qt::AlignLeft:
    {
        x1 = 0;
        x2 = m_view->width() - padding;
        break;
    }
    case Qt::Vertical | Qt::AlignRight:
    {
        x1 = padding;
        x2 = m_view->width();
        break;
    }
    case Qt::Vertical | Qt::AlignCenter:
    {
        x1 = padding;
        x2 = m_view->width() - padding;
        break;
    }
    case Qt::Horizontal | Qt::AlignTop:
    {
        y1 = 0;
        y2 = m_view->height() - padding;
        break;
    }
    case Qt::Horizontal | Qt::AlignBottom:
    {
        y1 = padding;
        y2 = m_view->height();
        break;
    }
    case Qt::Horizontal | Qt::AlignCenter:
    {
        y1 = padding;
        y2 = m_view->height() - padding;
        break;
    }
    }

    rect.setCoords(x1, y1, x2, y2);
    return rect;
}
