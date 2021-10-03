
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

#include "qbrush.h"
#include "qcolor.h"
#include "qfont.h"
#include "qwidget.h"
#include "qsize.h"
#include "qrect.h"

#include "Qt"

#include <vector>

class QKeyEvent;
class QPainter;
class QPaintEvent;
class QWidget;

class LinearGauge : public QWidget
{
public:
    LinearGauge(QWidget* parent = nullptr);

    LinearGauge(const LinearGauge&) = delete;
    LinearGauge& operator =(const LinearGauge&) = delete;

    LinearGauge(LinearGauge&&) = delete;
    LinearGauge& operator =(LinearGauge&&) = delete;

    ~LinearGauge() override;

    void setTickInterval(unsigned long interval);

    /**
     * @brief   Returns the current widget orientation.
     */
    Qt::Orientation orientation() const;

    /**
     * @brief   Sets the orientation of linear gauge widget
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * @brief   TextItem alignment of the tick's value.
     */
//        enum Alignment { AlignLeft = 2, AlignRight = 4, AlignCenter = 8, AlignTop = 16, AlignBottom = 32 };

    /**
     * @brief   Returns the tick's value text alignment.
     */
    Qt::Alignment alignment() const;

    /**
     * @brief   Sets the text alignment of tick's value.
     */
    void setAlignment(Qt::Alignment alignment);

    /**
     * @brief   Side of widget's border.
     */
    enum Border { Left, Right, Top, Bottom, AllBorder };

    /**
     * @brief   Returns the current borders.
     */
    Border border() const;

    /**
     * @brief   Sets borders of linear gauge.
     */
    void setBorder(Border border);

    /**
     * @brief   Returns true whether the widget's border is visible.
     */
    bool borderVisible() const;

    /**
     * @brief   Make widget's border visible.
     */
    void setBorderVisible(bool visible);

    void setFont(const QFont& font);

    /**
     * @brief   Returns the current number of digits.
     */
    unsigned long digitCount() const;

    /**
     * @brief   Sets the number of digits that are used to adjust tick's width depending on the
     *          reserved tick value's width.
     */
    void setDigitCount(unsigned long numDigits);

    void setBackgroundPalette(const QPalette& palette);

//    unsigned long largeTickInterval() const;
//    void setLargeTickInterval(unsigned long interval);

    void setLargeTickCount(unsigned long numTicks);

    /**
     * @brief   Returns the current number of ticks.
     */
    unsigned long tickCount() const;

    /**
     * @brief   Sets the number of ticks that are used from the top to the center of the widget.
     */
    void setTickCount(unsigned long numTicks);

    /**
     * @brief   Returns the current number of ticks.
     */
    unsigned long middleTickCount() const;

    /**
     * @brief   Sets the number of ticks that are used from the top to the center of the widget.
     */
    void setMiddleTickCount(unsigned long numTicks);

    /**
     * @brief   Returns the current number of ticks.
     */
    unsigned long smallTickCount() const;

    /**
     * @brief   Sets the number of ticks that are used from the top to the center of the widget.
     */
    void setSmallTickCount(unsigned long numTicks);

    /**
     * @brief   Returns true whether the text of ticks' value is visible.
     */

//                    Refresh each time value changed
    bool textVisible() const;

    /**
     * @brief   Sets whether the text of ticks' value is visible.
     */
    void setTextVisible(bool visible);

    /**
     * @brief   Returns true whether the ground is visible.
     */
    bool groundVisible() const;

    /**
     * @brief   Returns true whether the ground is visible.
     */
    void setGroundVisible(bool visible);

    /**
     * @brief   Returns the current value.
     */
    float value() const;

    /**
     * @brief   Sets value of linear gauge.
     */
    void setValue(float value);

    /**
     * @brief   Sets the value of the linear gauge to zero.
     */
    void reset();

    /**
     * @brief   Returns the current brush.
     */
    const QBrush& brush() const;

    /**
     * @brief   Sets the brush of linear gauge
     */
    void setBrush(const QBrush& brush);

//        template <typename T>
//        void setData(const T* data);

protected:

    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    void initPainter(QPainter* painter) const override;

signals:
    void requestDataUpdate();

private:

    float m_largeTickInterval;

    /**
     * @brief   Draws large ticks depending on the given rectangle.
     */
    void drawLargeTicks(QPainter& painter, unsigned long count, float offset);

    /**
     * @brief   Draws medium ticks depending on the given rectangle.
     */
    void drawMiddleTicks(QPainter& painter, unsigned long count, float offset);

    /**
     * @brief   Draws the widget's border depending on Border.
     */
    void drawBorder(QPainter& painter) const;

    /**
     * @brief   Draws the path over the ground (i.e. values that cannot be reached).
     */
    void drawGround(QPainter& painter, const QRect& rect, const QBrush& brush);

    void drawGround(QPainter& painter, int y);

    // to template
    int getNumber(unsigned long pos) const;

    void drawLargeTicksLabel(QPainter& painter, unsigned long count, float offset);

    void getTickPosition(QRect& rect, int thickness, int padding);
    void getTickLabel(QRect& rect, unsigned long padding);

    void initializeTicksLabelValue(float value, unsigned long count, float interval);

    /**
     * @brief   Set text items position within the widget depending on Qt::Orientation
     *          and Qt::Alignment
     */
    void initializeTicksLabelPosition(Qt::Orientation orientation, Qt::Alignment alignment);

    bool m_textVisible; //<! This property holds whether the text of ticks' value is visible;
    bool m_borderVisible; //<! This property holds whether the widget's borders are visible.
    bool m_groundVisible; //<! This property holds whether the ground is visible.

    float m_value; //!< Currrent value of the linear gauge.
    float m_interval; //<! Interval between values of the linear gauge.

    int m_padding; //<! Padding wrapping the text of the tick's value.

    unsigned long m_digitCount; //!< Maximum number of digits for tick's value.

    Qt::Alignment m_alignment; //<! Widget's side on which the step values will be drawn.

    Qt::Orientation m_orientation;

    Border m_border;

    // TODO: to replace with TextItem.boundingRect()
    QRect m_largeTickLabelRect;
    QRect m_largeTickLabelRectLeft;
    QRect m_largeTickLabelRectRight;
    QRect m_largeTickLabelRectTop;
    QRect m_largeTickLabelRectBottom;

    Qt::Alignment m_tickLabelAlignment; //!< Drawn value's text alignment

    // TODO
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

    unsigned long m_largeTickCount; //!< Number of large tick above or below the centered tick
    unsigned long m_middleTickCount; //!< Number of middle tick between large tick
    unsigned long m_smallTickCount; //!< Number of small tick between middle tick

    QRect m_largeTickRect;
    QRect m_middleTickRect;
    QRect m_smallTickRect;

    // TODO
    //
    // Create a paint model for font properties
    //
    // struct FontSettings
    // {
    //      QFont font;
    //      QSize fontSize;
    // };
    //
    // FontSettings m_fontSettings;
    //

    QFont m_font; //!< Font of the ticks' value.
    QSize m_fontSize;

    std::vector<int> m_vector; //!< Temporary container used to store data that will be displayed

    // TODO
    //
    // Create a paint model for color properties
    //
    // struct ColorSettings
    // {
    //      QBrush brush;
    //      QColor tickFillColor;
    //      QColor tickBorderColor;
    // };
    //
    // ColorSettings m_colorSettings;
    //

    QBrush m_brush;
    QColor m_tickFillColor;
    QColor m_tickBorderColor;

//        std::shared_ptr<AxisData> m_axisData;
};

#endif
