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

uint64_t CalcRandomCoeff( uint64_t n )
{
    return std::rand() % ( 1 << ( n + 1 ) );
}

////////////////////////////////////////////////////////////////////////////////

}  // namepace

////////////////////////////////////////////////////////////////////////////////

bool Message::OnTick()
{
    switch( GetState() )
    {
        case State::Waiting:
        {
            if( backoff_time_ > Clock::GetTime() )
                break;

            if( num_retries_ > 15 )
            {
                state_ = State::Dropped;
            }
            else
            {
                state_ = State::Sending;
                start_time_ = Clock::GetTime();
                last_time_ = start_time_;
            }
            break;
        }

        case State::Sending:
        {
            uint64_t delta_bits = ( Clock::GetTime() - last_time_ ) / BIT_TIME;
            sended_bits_ += delta_bits;
            last_time_ += delta_bits * BIT_TIME;

            if( sended_bits_ >= bits_size_ )
                state_ = State::Sended;
            break;
        }

        default:
            break;
    }

    return GetState() == State::Sending;
}

////////////////////////////////////////////////////////////////////////////////

void Message::OnCollision()
{
    ++num_retries_;

    state_ = State::Waiting;
    sended_bits_ = 0;

    backoff_time_ = Clock::GetTime() + CalcRandomCoeff( num_retries_ ) * TICK_TIME;
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace NCsmaCd

////////////////////////////////////////////////////////////////////////////////