
/**
 * @file	linear_gauge.h
 *
 * @brief	linear_gauge.h file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#ifndef __LINEAR_GAUGE_H
#define __LINEAR_GAUGE_H

#include "gauge_indicator/abstract_gauge.h"

#include "namespace.h"

#include "qbrush.h"
#include "qcolor.h"
#include "qfont.h"
#include "qrect.h"
#include "qsize.h"

#include "Qt"

#include <vector>

class QKeyEvent;
class QPainter;
class QPaintEvent;
class QWidget;

class LinearGauge : public AbstractGauge
{
  public:
    LinearGauge(QWidget* parent = nullptr);

    ~LinearGauge() override;

    bool groundVisible() const;
    void setGroundVisible(bool visible);

    int borderPosition() const;
    void setBorderPosition(int flags);
    bool borderVisible() const;
    void setBorderVisible(bool visible);

    int borderWidth() const;
    void setBorderWidth(int width);

    const QBrush& brush() const;
    void setBrush(const QBrush& brush);

  protected:
    void initPainter(QPainter* painter) const override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

  private:
    float g_largeTickPositionInterval;

    // Helpers for drawing ticks and labels
    void drawLargeTicks(QPainter& painter, unsigned long count, float offset);
    void drawMiddleTicks(QPainter& painter, unsigned long count, float offset);
    void drawSmallTicks(QPainter& painter, unsigned long count, float offset);
    void drawLargeTicksLabel(QPainter& painter, unsigned long count, float offset);

    // Helpers for setting the rectangle of ticks and labels
    void getTickPosition(QRect& rect, int thickness, int padding);
    void setTicksLabelPosition(Qt::Orientation orientation, TicksPosition position);

    int m_borderPosition;
    bool m_borderVisible; //<! This property holds whether the widget's borders are visible.
    bool m_groundVisible; //<! This property holds whether the ground is visible.

    // TODO: to replace with TextItem.boundingRect()
    QRect m_largeTickLabelRect;
    QRect m_largeTickLabelRectLeft;
    QRect m_largeTickLabelRectRight;
    QRect m_largeTickLabelRectTop;
    QRect m_largeTickLabelRectBottom;

    // TODO:
    //
    // Create a paint model for tick properties
    //
    // struct TickSettings
    // {
    //     unsigned long largeTickCount = 3ul;
    //     unsigned long middleTickCount = 4ul;
    //     unsigned long smallTickCount = 0ul;
    //     QRect largeTickRect;
    //     QRect middleTickRect;
    //     QRect smallTickRect;
    // };
    //
    // TickSettings m_tickSettings;
    //

    QRect m_largeTickRect;
    QRect m_middleTickRect;
    QRect m_smallTickRect;

    Q_DISABLE_COPY(LinearGauge);
};

#endif
