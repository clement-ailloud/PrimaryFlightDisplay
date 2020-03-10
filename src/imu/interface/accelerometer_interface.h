
#include "axis.h"


class IAccelerometer
{
    public:

        IAccelerometer();

        IAccelerometer(const IAccelerometer& accelerometer);

        virtual ~IAccelerometer();


    private:

        Axis m_axis;
};
