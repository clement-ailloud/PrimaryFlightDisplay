/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#include <string>
#include <vector>

using QString = std::string;

class GaugeData
{
public:
};

template <class T> class GaugeDataPrivate : public GaugeData
{
public:
    GaugeDataPrivate() = default;

    explicit GaugeDataPrivate(std::size_t count, T value = T())
        : m_data(count, value)
    {
    }

public:
    void push(T value) { m_data.push_back(value); }

    T& operator[](unsigned long pos) { return m_data[pos]; }

protected:
    std::vector<T> m_data;
};

using GaugeDataInt = GaugeDataPrivate<int>;
using GaugeDataFloat = GaugeDataPrivate<float>;
using GaugeDataString = GaugeDataPrivate<QString>;
