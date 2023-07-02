
/**
 * @file	linear_gauge.h
 *
 * @brief	linear_gauge.h file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#ifndef ABSTRACT_GAUGE_H
#define ABSTRACT_GAUGE_H

#include "qwidget.h"

class AbstractGauge : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER true)

public:
    explicit AbstractGauge(QWidget* parent = nullptr);

    AbstractGauge(const AbstractGauge&) = delete;
    AbstractGauge& operator=(const AbstractGauge&) = delete;

    AbstractGauge(AbstractGauge&&) = delete;
    AbstractGauge& operator=(AbstractGauge&&) = delete;

    ~AbstractGauge() override;

    enum TicksPosition
    {
        TicksLeft = 4,
        TicksRight = 8,
        TicksCenter = 16,
        TicksAbove = 32,
        TicksBelow = 64
    };
    Q_ENUM(TicksPosition);

    Qt::Alignment alignment() const;

    Qt::Orientation orientation() const;

    TicksPosition ticksPosition() const;

    bool labelVisible() const;
    void setLabelVisible(bool visible);

    const QFont& font() const;
    void setFont(const QFont& font);

    float minimum() const;
    void setMinimum(float);

    float maximum() const;
    void setMaximum(float);

    unsigned long largeTickCount() const;
    void setLargeTickCount(unsigned long numTicks);

    unsigned long middleTickCount() const;
    void setMiddleTickCount(unsigned long numTicks);

    unsigned long smallTickCount() const;
    void setSmallTickCount(unsigned long numTicks);

    unsigned long largeTickInterval() const;
    void setLargeTickInterval(unsigned long interval);

    float value() const;

public slots: // NOLINT(clang-diagnostic-error)
    void setAlignment(Qt::Alignment);
    void setOrientation(Qt::Orientation);
    void setTicksPosition(TicksPosition postition);
    void setRange(float min, float max);
    void setValue(float value);
    void reset();

signals:
    void valueChanged(int value);
    void rangeChanged(int min, int max);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    virtual void update(std::vector<QString>& labels);

private:
    Qt::Alignment m_alignment;
    Qt::Orientation m_orientation;
    TicksPosition m_ticksPosition;

    QFont m_font;
    bool m_labelVisible;

    float m_minimum;
    float m_maximum;

    float m_largeTickInterval;
    float m_largeTickCount;
    float m_middleTickCount;
    float m_smallTickCount;

    float m_value;

protected:
    QSize m_fontSize;
};

Qt::Alignment getLabelAlignment(AbstractGauge::TicksPosition position);

#endif // ABSTRACT_GAUGE_H
