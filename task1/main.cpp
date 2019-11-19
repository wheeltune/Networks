#include <iostream>

#include "network.hpp"
#include "logger.hpp"


////////////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{
    if( argc == 1 )
    {
        std::cout << "Usage: ./task1 num_nodes [ is_debug = 0 ]" << std::endl;
        return 1;
    }

    if( argc > 2 )
    {
        if( std::atoi( argv[ 2 ] ) == 1 )
            NLogger::Logger::SetLogLevel( NLogger::Logger::LogLevel::Debug );
    }

    std::srand( unsigned( std::time( 0 ) ) );

    NCsmaCd::Network network( std::atoi( argv[ 1 ] ) );
    network.Run();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////