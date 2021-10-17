/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include "altitude_indicator_view.h"

#include "gauge_indicator/linear_gauge.h"
//#include "linear_gauge_value.h"

#include "QHBoxLayout"

using namespace View;

AltitudeIndicator::AltitudeIndicator(QWidget* parent)
    : QWidget(parent)
    , m_linearLayout(new QHBoxLayout())
    , m_linearGauge(new LinearGauge(this))
// , m_linearGaugeValue(new LinearGaugeValue(*m_linearGauge))
{
    m_linearGauge->setLargeTickInterval(10);
    m_linearGauge->setAlignment(Qt::AlignLeft);
    m_linearGauge->setTicksPosition(AbstractGauge::TicksPosition::TicksLeft);
    m_linearGauge->setBorderPosition(BorderPosition::BorderTop | BorderPosition::BorderLeft |
                                     BorderPosition::BorderBottom);
    m_linearGauge->setMiddleTickCount(1);
    QPalette palette;
    QColor backgroundColor("#7ec850");
    backgroundColor.setAlpha(64);
    palette.setColor(QPalette::Window, backgroundColor);
    m_linearGauge->setAutoFillBackground(true);
    m_linearGauge->setPalette(palette);
    m_linearLayout->addWidget(m_linearGauge);
    setLayout(m_linearLayout);
}

AltitudeIndicator::~AltitudeIndicator() = default;

int AltitudeIndicator::altitude() const
{
    return m_linearGauge->value();
}

void AltitudeIndicator::setAltitude(int altitude)
{
    m_linearGauge->setValue(altitude);
}
