#include "Invoker.hpp"
#include "NickCommand.hpp"
#include "HelpCommand.hpp"
#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "LeaveCommand.hpp"
#include "WhoCommand.hpp"
#include "ListCommand.hpp"

Invoker::Invoker(Server *server) : _server(server) {
	_commands.push_back(new HelpCommand("/help"));
	_commands.push_back(new NickCommand("/nick"));
	_commands.push_back(new JoinCommand("/join"));
	_commands.push_back(new LeaveCommand("/leave"));
	_commands.push_back(new WhoCommand("/who"));
	_commands.push_back(new KickCommand("/kick"));
	_commands.push_back(new ListCommand("/list"));
}

void	Invoker::processCommand(User* sender, deque<string> args) {
	string commandName = args[0];
	args.pop_front();
	std::cout << commandName << " @" << sender->getName() << std::endl;
	for (size_t i = 0; i < _commands.size(); i++) {
		if (commandName == _commands[i]->getName()) {
			_commands[i]->setServer(_server);
			_commands[i]->setSender(sender);
			_commands[i]->setArgs(args);
			try {
				_commands[i]->execute();
			} catch(const char* message) {
				sender->getReply("Error" + string(message));
			}
			break;
		}
	}
}

void	Invoker::processData(User *sender, std::string data) {
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
		cout << "seding message" << endl;
		sender->sendMessageToChannel(data);
	}
}
