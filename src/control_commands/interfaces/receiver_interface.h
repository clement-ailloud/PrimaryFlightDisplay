//!
//! \file	receiver_interface.h
//!
//! \brief	Interface allowing to bind a command to a receiver
//!
//! \date	Friday, February 21th
//!
//! \author     Clement Ailloud
//!


namespace Command
{

class IReceiver
{
    public:

	IReceiver(const IReceiver& other) = default;
	IReceiver(IReceiver&& other) = default;

	IReceiver& operator =(const IReceiver& other) = default;
	IReceiver& operator =(IReceiver&& other) = default;

    protected:

	IReceiver() = default;

	virtual ~IReceiver() = default;
};

}
