#include "network.hpp"

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

}  // namespace

////////////////////////////////////////////////////////////////////////////////

Network::Network( size_t num_nodes )
{
    nodes_.reserve( num_nodes );
    for( uint64_t i = 0; i < num_nodes; ++i )
        nodes_.emplace_back( i );
}

////////////////////////////////////////////////////////////////////////////////

void Network::Run()
{
    bool has_messages = true;
    while( has_messages )
    {
        std::vector< bool > is_message( nodes_.size(), false );

        size_t is_busy = ( owner_ != nullptr );
        if( owner_ != nullptr )
            is_busy = owner_->OnTick( is_busy );

        for( size_t i = 0; i < nodes_.size(); ++i )
        {
            if ( owner_ != &nodes_[ i ] )
                is_message[ i ] = nodes_[ i ].OnTick( is_busy );
            else
                is_message[ i ] = is_busy;
        }

        if( !is_busy )
        {
            size_t count_messages = 0;
            for( bool check : is_message )
                count_messages += check;

            if( count_messages > 1 )
            {
                for( size_t i = 0; i < nodes_.size(); ++i )
                {
                    if( is_message[ i ] )
                        nodes_[ i ].OnCollision();
                }
            }
            else
            {
                for( size_t i = 0; i < nodes_.size(); ++i )
                {
                    if( is_message[ i ] )
                    {
                        owner_ = &nodes_[ i ];
                        break;
                    }
                }
            }
        }

        Clock::Tick();

        has_messages = false;
        for( const Node & node : nodes_ )
            has_messages |= node.HasMessage();
    }
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace NCsmaCd

////////////////////////////////////////////////////////////////////////////////