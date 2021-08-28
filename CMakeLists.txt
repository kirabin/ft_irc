cmake_minimum_required(VERSION 3.19)
project(irc_server)

set(CMAKE_CXX_STANDARD 98)

add_executable(irc_server src/Channel/Channel.cpp src/Invoker/Command.cpp src/Invoker/Commands/HelpCommand.cpp src/Invoker/Invoker.cpp src/Invoker/Commands/JoinCommand.cpp src/Invoker/Commands/KickCommand.cpp src/Invoker/Commands/LeaveCommand.cpp src/Invoker/Commands/NickCommand.cpp src/Invoker/Commands/WhoCommand.cpp src/Server/Server.cpp src/User/User.cpp src/Utils/utils.cpp
        src/Channel/Channel.hpp src/Invoker/Command.hpp src/Invoker/Commands/HelpCommand.hpp src/Invoker/Invoker.hpp src/Invoker/Commands/JoinCommand.hpp src/Invoker/Commands/KickCommand.hpp src/Invoker/Commands/LeaveCommand.hpp src/Invoker/Commands/NickCommand.hpp src/Invoker/Commands/WhoCommand.hpp src/Server/Server.hpp src/User/User.hpp src/Utils/ircserv.hpp
      main.cpp src/Invoker/Commands/ListCommand.cpp src/Invoker/Commands/ListCommand.cpp src/Invoker/Commands/PassCommand.cpp src/Invoker/Commands/PassCommand.hpp src/Invoker/Commands/QuitCommand.cpp src/Invoker/Commands/QuitCommand.hpp     src/Invoker/Commands/ErrorCommand.cpp src/Invoker/Commands/ErrorCommand.hpp src/Invoker/Commands/UserCommand.cpp src/Invoker/Commands/UserCommand.hpp)
