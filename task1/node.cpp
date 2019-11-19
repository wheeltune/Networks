#include "network.hpp"

#include <iostream>
#include <iomanip>

#include "logger.hpp"
#include "clock.hpp"


////////////////////////////////////////////////////////////////////////////////

namespace NCsmaCd
{

////////////////////////////////////////////////////////////////////////////////

namespace
{

////////////////////////////////////////////////////////////////////////////////

using NClock::Clock;

////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////

bool Node::OnTick( bool is_busy )
{
    if( message_ == nullptr )
        return false;

    bool is_sending = false;
    if( !is_busy || message_->GetState() == Message::State::Sending )
        is_sending = message_->OnTick();

    if( message_->GetState() == Message::State::Sended )
    {
        LOG_DEBUG( "Message sended (id=" + std::to_string( id_ ) + ")" );
        std::cout << "Node with id = " << std::setfill( '0' ) << std::setw( 3 )
                  << GetId() << " will send message at "
                  << Clock::FormatTime( message_->GetStartTime() )
                  << " with attempt " << std::setfill( '0' ) << std::setw( 2 )
                  << message_->GetNumRetries() + 1 << std::endl;
        message_ = nullptr;
    }
    else if( message_->GetState() == Message::State::Dropped )
    {
        LOG_DEBUG( "Message dropped (id=" + std::to_string( id_ ) + ")" );
        std::cout << "Node with id = " << std::setfill( '0' ) << std::setw( 3 )
                  << GetId() << " will not send message" << std::endl;
        message_ = nullptr;
    }

    return is_sending;
}

////////////////////////////////////////////////////////////////////////////////

void Node::OnCollision()
{
    LOG_DEBUG( "Collision detected (id=" + std::to_string( id_ ) + ")" );
    message_->OnCollision();
}

////////////////////////////////////////////////////////////////////////////////

bool Node::HasMessage() const
{
    return message_ != nullptr;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace NCsmaCd

////////////////////////////////////////////////////////////////////////////////