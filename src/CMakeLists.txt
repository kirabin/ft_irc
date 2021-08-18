cmake_minimum_required(VERSION 3.19)
project(irc_server)

set(CMAKE_CXX_STANDARD 98)

add_executable(irc_server lib/Channel/Channel.Class.hpp lib/Executor/Executor.Class.hpp lib/Utils/ircserv.hpp lib/Server/Server.Class.hpp lib/User/User.Class.hpp lib/Channel/Channel.Class.cpp lib/Executor/Executor.Class.cpp main.cpp lib/Server/Server.Class.cpp lib/User/User.Class.cpp lib/Utils/utils.cpp)