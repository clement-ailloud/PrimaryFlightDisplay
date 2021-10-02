//!
//! \file
//!
//! \brief
//!
//! \date
//!
//! \author     Clement Ailloud
//!
//! \license
//!



namespace View
{

    /*---------------------------------------------------------------------------------------------
     * @class	IPrimaryFlightDisplay
     *---------------------------------------------------------------------------------------------
     * @brief	Interface displaying the primary flight display panel.
     *
     *		Composed of:
     *		===========
     *		- speed indicator
     *		- vertical speed indicator
     *		- attitude indicator
     *		- altitude indicator
     *		- heading indicator
     *
     *		Input controls:
     *		==============
     *		- joystick controller left
     *		- joystick controller right
     *		- light button
     *		- map button
     *		- camera button (long press -> dialog camera settings with tab panels)
     *		- application settings button (change of display, dark/light mode,
     *		    switch joystick controller)
     *		- remote settings button (drone settings)
     *		- control auto-calibration button (maybe insteaf of trim buttons)
     *		- trim left button (arc display +/- on each side)
     *		- trim right button
     *		- night mode button
     *		- home button
     *		- gps button
     *-------------------------------------------------------------------------------------------*/

class IPrimaryFlightDisplayView
{
    public:

        IPrimaryFlightDisplayView() = default;

        IPrimaryFlightDisplayView(const IPrimaryFlightDisplayView&) = delete;
        IPrimaryFlightDisplayView(IPrimaryFlightDisplayView&&) = delete;

        virtual ~IPrimaryFlightDisplayView() = default;

        IPrimaryFlightDisplayView& operator =(const IPrimaryFlightDisplayView&) = delete;
        IPrimaryFlightDisplayView& operator =(IPrimaryFlightDisplayView&&) = delete;


	/*
	 * @fn	    setSpeed(float speed)
	 *
	 * @brief   Set the real speed
	 *
	 * @param   speed
	 */

        virtual void setSpeed(float) = 0;


	/*
	 * @fn	    setVerticalSpeed(float speed)
	 *
	 * @brief   Set the vertical speed
	 *
	 * @param   speed
	 */

        virtual void setVerticalSpeed(float) = 0;


	/*
	 * @fn	    setAltitude(float altitude)
	 *
	 * @brief   Set the altitude
	 *
	 * @param   altitude
	 */

        virtual void setAltitude(float) = 0;


	/*
	 * @fn	    setHeading(float heading)
	 *
	 * @brief   Set the heading
	 *
	 * @param   heading
	 */

        virtual void setHeading(float) = 0;

	// Ensure the sensors'model will not affect the move controls (try...catch())


	// Input signals
//	void linearControlChanged(int x, int y)
//	void rotationControlChanged(int x, int y)
//	void lightTurnedOnRequested()
//	void lightTurnedOffRequested()
//	void gpsTurnedOnRequested()
//	void gpsTurnedOffRequested()
//        void mapOpenedRequested()
//        void mapClosedRequested()
//	void normalModeRequested()
//	void ecoModeRequested()
//	void sportModeRequested()
};

} // namespace View
