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

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    View::PrimaryFlightDisplay pfd;
    pfd.showMaximized();

    return QApplication::exec();
}
