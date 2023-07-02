/**
 * @file
 *
 * @brief
 *
 * @date
 *
 * @author     Clement Ailloud
 */

#ifndef REGISTER_HPP
#define REGISTER_HPP

template <int address, std::size_t N> class Register
{
public:
    explicit Register(ValueType value)
        : m_value(value)
        , m_address(address)
    {
    }

    int address() const { return m_address; }

    size_t size() const { return sizeof(ValueType); };

    ValueType value() const { return m_value; };
    void setValue(ValueType);

    Register& operator=(ValueType);

private:
    ValueType m_value;
    int m_address;
};

using CLK_RATE = Register<0x5341, sizeof(short)>;

#endif
