#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "logger.hpp"
#include "message.hpp"


////////////////////////////////////////////////////////////////////////////////

namespace NCsmaCd
{

////////////////////////////////////////////////////////////////////////////////

class Node
{
public:
    Node( uint64_t id )
    :   id_( id ), message_( std::make_unique< Message >() )
    {
        LOG_DEBUG( "Init node (id=" + std::to_string( id_ ) + ")" );
    }

    uint64_t GetId() const { return id_; }

    bool OnTick( bool is_busy );
    void OnCollision();

    bool HasMessage() const;

private:
    uint64_t id_;
    std::unique_ptr< Message > message_;
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace NCsmaCd

////////////////////////////////////////////////////////////////////////////////