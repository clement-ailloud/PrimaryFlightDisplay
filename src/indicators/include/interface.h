//!
//! \file
//!
//! \brief
//!
//! \date
//!
//! \author     Clement Ailloud
//!


#include <cmath>

#include <memory>


class
{

};

    initializePen();

    if (m_drawBorder)
    {
        drawBoundingRect(painter);
    }

    // Update drawn number
    std::vector<int> tab;

    // Remove the rest to keep the right step
    m_drawOffsetValue = m_value - std::fmod(m_value, m_stepValue);

    const int startValue = m_largeTick * m_stepValue + m_stepValue + m_drawOffsetValue;
    const int stopValue = -m_largeTick * m_stepValue + m_drawOffsetValue;

    // Fill array with step value
    for (auto i = startValue; i >= stopValue; i -= m_stepValue)
    {
        tab.push_back(i);
    }

    int j = 0;

    // Convert value into pixel offset
    const auto offset = std::fmod(valueToDraw(m_value, m_largeTickInterval / m_stepValue), 40.f);

    painter->setBrush(QBrush(QColor("#aa32cd32")));
    setPenColor();

    //!
    //! DRAW INDICATOR BACKGROUND
    //!

    for (auto i = m_drawStartY; i <= m_drawStopY; i += m_largeTickInterval)
    {
        const auto number = tab[j];

        // Do not print negative values
        if (number >= 0)
        {
            const auto y = i + offset + 1;

            // Recenter tick
            const auto yRect = y - m_drawRectHeight / 2;

            moveTop
            m_largeTickRect.moveTop(yRect);
            painter->drawRect(m_largeTickRect);
            // Draw large tick

            // Draw middle tick
            m_middleTickRect.moveTop(yRect - m_largeTickInterval / 2);
            painter->drawRect(m_middleTickRect);

            // Do not draw 0 value
            if (number > 0 && m_textVisible == true)
            {
                // Recenter text
                const auto yText = y - m_textHeight / 2;

                m_textRect.moveTop(yText);
                painter->drawText(m_textRect, m_textAlignment, QString::number(number));
            }
        }

        j++; // Get next value to draw
    }

    int yGround = (m_value * m_largeTickInterval) / m_stepValue;

    QLinearGradient linearGradient(m_boundingRect.topLeft(), m_boundingRect.bottomLeft());
    linearGradient.setColorAt(0, Qt::white);
    linearGradient.setColorAt(1, Qt::darkGreen);

    QRect rect(m_boundingRect.x(), yGround, m_boundingRect.width(), m_boundingRect.height());

    QBrush brush(linearGradient);

    drawGround(painter, rect, brush);
