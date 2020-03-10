//!
//! \file	command_interface.h
//!
//! \brief	Interface allowing to create commands for a specific receiver
//!
//! \date	Friday, February 21th
//!
//! \author     Clement Ailloud
//!


namespace Command
{

class IReceiver;


class ICommand
{
    public:

	ICommand() = default;
	ICommand(const IReceiver& receiver);

	ICommand(const ICommand&) = delete;
	ICommand(ICommand&&) = delete;

	virtual ~ICommand() = default;

	virtual void execute() = 0 const;
	virtual void unexecute() = 0 const;

	ICommand& operator=(const ICommand&) = delete;
	ICommand& operator=(ICommand&&) = delete;

    private:

	const IReceiver& m_receiver;
};

}
