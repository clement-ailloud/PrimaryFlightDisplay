/**
 * @file	airspeed_indicator_view.cpp
 *
 * @brief	airspeed_indicator_view file description
 *
 * @date
 *
 * @author	Clement Ailloud
 */

#include "airspeed_indicator_view.h"

#include "gauge_indicator/linear_gauge.h"
//#include "linear_gauge_value.h"

#include "QHBoxLayout"
#include "QPalette"

using namespace View;

AirspeedIndicator::AirspeedIndicator(QWidget* parent)
    : QWidget(parent)
    , m_linearLayout(new QHBoxLayout())
    , m_linearGauge(new LinearGauge(this))
//    , m_linearGaugeValue(new LinearGaugeValue(*m_linearGauge))
{
    m_linearGauge->setAlignment(Qt::AlignRight);
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

AirspeedIndicator::~AirspeedIndicator() = default;

int AirspeedIndicator::speed() const
{
    return m_linearGauge->value();
}

void AirspeedIndicator::setSpeed(const int speed)
{
    m_linearGauge->setValue(speed);
}
