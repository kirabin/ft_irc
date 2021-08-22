cmake_minimum_required(VERSION 3.19)
project(irc_server)

set(CMAKE_CXX_STANDARD 98)

add_executable(irc_server lib/Channel/Channel.cpp lib/Invoker/Command.cpp lib/Invoker/HelpCommand.cpp lib/Invoker/Invoker.cpp lib/Invoker/JoinCommand.cpp lib/Invoker/KickCommand.cpp lib/Invoker/LeaveCommand.cpp lib/Invoker/NickCommand.cpp lib/Invoker/WhoCommand.cpp lib/Server/Server.cpp lib/User/User.cpp lib/Utils/utils.cpp
        lib/Channel/Channel.hpp lib/Invoker/Command.hpp lib/Invoker/HelpCommand.hpp lib/Invoker/Invoker.hpp lib/Invoker/JoinCommand.hpp lib/Invoker/KickCommand.hpp lib/Invoker/LeaveCommand.hpp lib/Invoker/NickCommand.hpp lib/Invoker/WhoCommand.hpp lib/Server/Server.hpp lib/User/User.hpp lib/Utils/ircserv.hpp
      main.cpp  lib/Invoker/ListCommand.cpp lib/Invoker/ListCommand.cpp)
