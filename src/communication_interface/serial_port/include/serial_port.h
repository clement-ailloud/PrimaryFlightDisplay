#ifndef __SERIAL_PORT_H
#define __SERIAL_PORT_H


#include "qserialport.h"


class SerialPort : public QSerialPort
{
    public:

        SerialPort(const QSerialPortInfo &serialPortInfo, QObject* parent = nullptr);

        virtual ~SerialPort();
};


#endif
