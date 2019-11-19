#include "clock.hpp"

#include <string>
#include <sstream>
#include <iomanip>


////////////////////////////////////////////////////////////////////////////////

namespace NClock
{

////////////////////////////////////////////////////////////////////////////////

std::string Clock::FormatTime( uint64_t time )
{
    uint64_t m_seconds = time / 10;
    uint64_t seconds = m_seconds / 1000000;
    uint64_t minutes = seconds / 60;
    uint64_t hours = minutes / 24;

    std::stringstream ss;
    ss << std::setfill( '0' ) << std::setw( 2 ) << hours % 24;
    ss << ":";
    ss << std::setfill( '0' ) << std::setw( 2 ) << minutes % 60;
    ss << ":";
    ss << std::setfill( '0' ) << std::setw( 2 ) << seconds % 60;
    ss << ",";
    ss << std::setfill( '0' ) << std::setw( 6 ) << m_seconds % 1000000;
    return ss.str();
}

////////////////////////////////////////////////////////////////////////////////

}  // namespace NClock

////////////////////////////////////////////////////////////////////////////////