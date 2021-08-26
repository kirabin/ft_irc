cmake_minimum_required(VERSION 3.19)
project(irc_server)

set(CMAKE_CXX_STANDARD 98)

add_executable(irc_server src/Channel/Channel.cpp src/Invoker/Command.cpp src/Invoker/HelpCommand.cpp src/Invoker/Invoker.cpp src/Invoker/JoinCommand.cpp src/Invoker/KickCommand.cpp src/Invoker/LeaveCommand.cpp src/Invoker/NickCommand.cpp src/Invoker/WhoCommand.cpp src/Server/Server.cpp src/User/User.cpp src/Utils/utils.cpp
        src/Channel/Channel.hpp src/Invoker/Command.hpp src/Invoker/HelpCommand.hpp src/Invoker/Invoker.hpp src/Invoker/JoinCommand.hpp src/Invoker/KickCommand.hpp src/Invoker/LeaveCommand.hpp src/Invoker/NickCommand.hpp src/Invoker/WhoCommand.hpp src/Server/Server.hpp src/User/User.hpp src/Utils/ircserv.hpp
      main.cpp src/Invoker/ListCommand.cpp src/Invoker/ListCommand.cpp src/Invoker/PassCommand.cpp src/Invoker/PassCommand.hpp)
