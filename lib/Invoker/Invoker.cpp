#include "Invoker.hpp"
#include "NickCommand.hpp"
#include "HelpCommand.hpp"
#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "LeaveCommand.hpp"
#include "WhoCommand.hpp"
#include "ListCommand.hpp"

// TODO # define PASS_DIS		"/pass <passwordtoserver> - kick a user from channel"
// TODO # define USER_DIS		"/user <username> <hostname> <servername> <realname> - used at the beginning of connection to specify you on server"

Invoker::Invoker(Server *server) : _server(server) {
	_commands.push_back(new HelpCommand(_commands));
	_commands.push_back(new NickCommand());
	_commands.push_back(new JoinCommand());
	_commands.push_back(new LeaveCommand());
	_commands.push_back(new WhoCommand());
	_commands.push_back(new KickCommand());
	_commands.push_back(new ListCommand());
}

Invoker::~Invoker() {
	// TODO delete commands
}

void	Invoker::processCommand(User* sender, deque<string> args) {
	string commandName = args[0];
	args.pop_front();
	for (size_t i = 0; i < _commands.size(); i++) {
		if (commandName == _commands[i]->getName()) {
			_commands[i]->setServer(_server);
			_commands[i]->setSender(sender);
			_commands[i]->setArgs(args);
			try {
				_commands[i]->execute();
			} catch(const char* message) {
				sender->getReply("Error: " + string(message));
			}
			break;
		}
	}
}

void	Invoker::processData(User *sender, std::string data) {

	std::cout << "@" << sender->getName() << " " << data;

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
