cmake_minimum_required(VERSION 3.0)

add_executable(task1 main.cpp network.cpp node.cpp message.cpp clock.cpp logger.cpp)

set_property(TARGET task1 PROPERTY CXX_STANDARD 17)