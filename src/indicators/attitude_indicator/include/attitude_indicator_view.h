#ifndef __ATTITUDE_INDICATOR_VIEW_H
#define __ATTITUDE_INDICATOR_VIEW_H


#include "QGraphicsItemGroup"
#include "QGraphicsLayoutItem"

#include <memory>

#include "qsize.h"


class QGraphicsItem;
class QGraphicsLayoutItem;
class LinearGauge;
// class FlightDirectorSystem;


namespace View
{

// TODO:  Singleton
class AttitudeIndicator : public QGraphicsItemGroup, public QGraphicsLayoutItem
{
    public:

        AttitudeIndicator(QGraphicsItem* parent = nullptr,
			  QGraphicsLayoutItem* parentLayout = nullptr);
        AttitudeIndicator(const AttitudeIndicator&) = delete;
	AttitudeIndicator(AttitudeIndicator&&) = delete;

        virtual ~AttitudeIndicator();

	void setBoundingRect(const QRectF& boundingRect);

	/*
	 * @fn	    setFlightDirectorSystem(FlightDirectorSystem& fds
	 *
	 * @brief   add information from the navigation system to facilitate the steering
	 *
	 * @param   FlightDirectorSystem&
	 */

//        void setFlightDirectorSystem(FlightDirectorSystem& fds);

	AttitudeIndicator& operator=(const AttitudeIndicator&) = delete;
	AttitudeIndicator& operator=(AttitudeIndicator&&) = delete;


    protected:

	QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const override;


    private:

	std::unique_ptr<LinearGauge> m_linearGauge;
};

}

#endif
