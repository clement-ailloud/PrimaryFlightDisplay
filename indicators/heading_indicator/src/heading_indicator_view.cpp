/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */


#include "heading_indicator_view.h"

#include "linear_gauge/linear_gauge.h"

#include "QColor"
#include "QHBoxLayout"
#include "QPalette"

using namespace View;

HeadingIndicator::HeadingIndicator(QWidget* parent)
    : QWidget(parent)
    , m_linearLayout(new QHBoxLayout())
    , m_linearGauge(new LinearGauge(this))
{
    m_linearGauge->setFont(QFont("Cantarell", 20));
    m_linearGauge->setAlignment(Qt::AlignBottom);
    m_linearGauge->setOrientation(Qt::Horizontal);
    m_linearGauge->setGroundVisible(false);
    m_linearGauge->setLargeTickCount(3);
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

HeadingIndicator::~HeadingIndicator() = default;

int HeadingIndicator::heading() const
{
    return m_linearGauge->value();
}

void HeadingIndicator::setHeading(int heading)
{
    m_linearGauge->setValue(heading);
}
