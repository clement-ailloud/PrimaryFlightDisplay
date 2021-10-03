#include "attitude_indicator_view.h"

#include "gauge_indicator/linear_gauge.h"
//#include "linear_gauge_value.h"

#include "QHBoxLayout"

//#include "attitude_indicator_symbol.h"

// Move assist
//#include "flight_director.h"

using namespace View;

AttitudeIndicator::AttitudeIndicator(QWidget* parent)
    : QWidget(parent)
    , m_linearLayout(new QHBoxLayout())
    , m_linearGauge(new LinearGauge(this))
// , m_attitudeIndicatorSymbol(new AttitudeIndicatorSymbol(this))
{
    m_linearGauge->setAlignment(Qt::AlignCenter);
    m_linearGauge->setTicksPosition(AbstractGauge::TicksPosition::TicksCenter);
    m_linearGauge->setLargeTickInterval(10);
    m_linearGauge->setLargeTickCount(2);
    m_linearGauge->setMiddleTickCount(1);
    m_linearGauge->setGroundVisible(false);

    m_linearLayout->addWidget(m_linearGauge);
    setLayout(m_linearLayout);
}

AttitudeIndicator::~AttitudeIndicator() = default;
