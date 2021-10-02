/*
 * @file	main.cpp
 *
 * @brief
 *
 * @date
 *
 * @author	Clement Ailloud
 */



#include "qapplication.h"

#include "primary_flight_display_view.h"

//#include "linear_gauge.h"

//#include "virtual_joystick_controller.h"

/*
 * @fn		main
 *
 * @brief	main    function description
 *
 * @param	argc	arguments count
 *
 * @param	argv	arguments vector
 */

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    View::PrimaryFlightDisplay pfd;
    pfd.showMaximized();

//    LinearGauge gauge;
//    gauge.showMaximized();

    return QApplication::exec();
}
