
#include "axis.h"


class IGyroscope
{
    public:

        IGyroscope();

        IGyroscope(const IGyroscope& gyroscope);

        ~IGyroscope();


    private:

        Axis m_axis;
};
