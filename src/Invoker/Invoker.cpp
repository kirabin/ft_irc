#include "Invoker.hpp"
#include "Commands/NickCommand.hpp"
#include "Commands/HelpCommand.hpp"
#include "Commands/JoinCommand.hpp"
#include "Commands/KickCommand.hpp"
#include "Commands/LeaveCommand.hpp"
#include "Commands/WhoCommand.hpp"
#include "Commands/ListCommand.hpp"
#include "Commands/PassCommand.hpp"

Invoker::Invoker(Server *server) : _server(server) {
	_commands.push_back(new HelpCommand(_commands));
	_commands.push_back(new NickCommand());
	_commands.push_back(new JoinCommand());
	_commands.push_back(new LeaveCommand());
	_commands.push_back(new WhoCommand());
	_commands.push_back(new KickCommand());
	_commands.push_back(new ListCommand());
	_commands.push_back(new PassCommand());
}

Invoker::~Invoker() {
	vector<Command*>::iterator it;

	// TODO: how to close a server?
	for (it = _commands.begin(); it != _commands.end(); it++) {
		delete *it;
	}
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
				sender->getReply(string(message));
				sender->getReply("");
			} catch(string message) {
				sender->getReply(message);
				sender->getReply("");
			}
			return ;
		}
	}
	sender->getReply("Error: No such command");
	sender->getReply("");
}

bool	Invoker::isCommand(std::string data) {
	vector<Command*>::iterator it;

	for (it = _commands.begin(); it != _commands.end(); it++) {
		if ((*it)->getName() == data) {
			return true;
		}
	}
	return false;
}

void	Invoker::processData(User *sender, std::string data) {

	std::cout << "@" << sender->getName() << " " << data;

	stringstream	ssMsg(data);
	string			av;
	deque<string>	arguments;

	while (getline(ssMsg, av, ' '))
	{
		av.erase(av.find_last_not_of("\n\r") + 1);
		if (!av.empty())
			arguments.push_back(av);
	}

	if (isCommand(arguments[0])) {
		processCommand(sender, arguments);
	} else {
		sender->sendMessageToChannel(data);
	}

}
