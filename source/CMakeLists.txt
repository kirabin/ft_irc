cmake_minimum_required(VERSION 3.19)
project(irc_server)

set(CMAKE_CXX_STANDARD 98)

add_executable(irc_server lib/Channel/Channel.hpp lib/Executor/Executor.hpp lib/Utils/ircserv.hpp lib/Server/Server.hpp lib/User/User.hpp lib/Channel/Channel.cpp lib/Executor/Executor.cpp main.cpp lib/Server/Server.cpp lib/User/User.cpp lib/Utils/utils.cpp lib/Executor/NickCommand.cpp lib/Executor/NickCommand.hpp )
