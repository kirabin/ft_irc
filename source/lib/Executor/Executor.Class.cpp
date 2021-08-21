#include "Executor.Class.hpp"
#include "NickCommand.hpp"
#include "HelpCommand.hpp"
#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "LeaveCommand.hpp"
#include "WhoCommand.hpp"

Executor::Executor(Server *server) : _server(server)
{
	_commands.push_back(new HelpCommand("/help"));
	_commands.push_back(new NickCommand("/nick"));
	_commands.push_back(new JoinCommand("/join"));
	_commands.push_back(new LeaveCommand("/leave"));
	_commands.push_back(new WhoCommand("/who"));
	_commands.push_back(new KickCommand("/kick"));
}

void	Executor::processCommand(User* sender, deque<string> arguments)
{
	string commandName = arguments[0];
	arguments.pop_front();
	std::cout << commandName << std::endl;
	for (size_t i = 0; i < _commands.size(); i++) {
		if (commandName == _commands[i]->getName()) {
			_commands[i]->execute(_server, sender, arguments);
			break;
		}
	}
}

void	Executor::processData(User *sender, std::string data)
{
	if (data[0] == '/') {  // data.isCommand()
		// split
		stringstream	ssMsg(data);
		string			av;
		deque<string>	arguments;

		while (getline(ssMsg, av, ' '))
		{
			av.erase(av.find_last_not_of(ENDL) + 1);
			arguments.push_back(av);
		}
		/////////////////////

		processCommand(sender, arguments);
	} else {
		sender->sendMessageToChannel(data);
	}
}


// void			Executor::sendErrorReply(std::string info)
// {
// 	std::string	msgReply = _server->getSign() + SPC + info + ENDL;
// 	send(_sender->getSockFd(), msgReply.c_str(), msgReply.length(), SEND_OPT);
// }
