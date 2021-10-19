/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#ifndef __HEADING_INDICATOR_VIEW_H
#define __HEADING_INDICATOR_VIEW_H

#include "qwidget.h"

#include "qpointer.h"

class QHBoxLayout;
class LinearGauge;

namespace View
{

class HeadingIndicator : public QWidget
{
public:
    HeadingIndicator(QWidget* parent = nullptr);

    // Copy constructor and assignment
    HeadingIndicator(const HeadingIndicator&) = delete;
    HeadingIndicator& operator=(const HeadingIndicator&) = delete;

    // Move constructor and assignment
    HeadingIndicator(HeadingIndicator&&) = delete;
    HeadingIndicator& operator=(HeadingIndicator&&) = delete;

    ~HeadingIndicator() override;

    int heading() const;
    void setHeading(int heading);

private:
    QPointer<QHBoxLayout> m_linearLayout;
    QPointer<LinearGauge> m_linearGauge;
};

} // namespace View

#endif
