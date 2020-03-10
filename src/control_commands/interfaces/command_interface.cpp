//!
//! \file	command_interface.cpp
//!
//! \brief
//!
//! \date
//!
//! \author     Clement Ailloud
//!


#include "command_interface.h"

#include "receiver_interface.h"


using namespace Command;


ICommand::ICommand(const IReceiver& receiver)
    : m_receiver(receiver)
{
}
