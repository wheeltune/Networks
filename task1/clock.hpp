#pragma once

#include <cstdint>
#include <string>

#include "constants.hpp"


////////////////////////////////////////////////////////////////////////////////

namespace NClock
{

////////////////////////////////////////////////////////////////////////////////

class Clock
{
public:
    static uint64_t GetTime()
    {
        return GetInstance().GetTimeImpl();
    }

    static void Tick()
    {
        return GetInstance().TickImpl();
    }

    static std::string FormatTime( uint64_t time );

private:
    Clock() {}

    Clock( const Clock & other ) = delete;
    Clock( Clock && other ) = delete;

    Clock & operator=( const Clock & other ) = delete;
    Clock & operator=( Clock && other ) = delete;

    static Clock & GetInstance()
    {
        static Clock instance;
        return instance;
    }

    void TickImpl() { time_ += TICK_TIME; }
    uint64_t GetTimeImpl() { return time_; }

private:
    uint64_t time_ = 0;
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace NClock

////////////////////////////////////////////////////////////////////////////////