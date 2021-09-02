#include "Invoker.hpp"
#include "Commands/NickCommand.hpp"
#include "Commands/HelpCommand.hpp"
#include "Commands/JoinCommand.hpp"
#include "Commands/KickCommand.hpp"
#include "Commands/PartCommand.hpp"
#include "Commands/WhoCommand.hpp"
#include "Commands/ListCommand.hpp"
#include "Commands/PassCommand.hpp"
#include "Commands/ErrorCommand.hpp"
#include "Commands/QuitCommand.hpp"
#include "Commands/UserCommand.hpp"
#include "Commands/NoticeCommand.hpp"
#include "Commands/PrivateMessageCommand.hpp"

Invoker::Invoker(Server *server) : _server(server) {
	_commands.push_back(new HelpCommand(_commands));
	_commands.push_back(new NickCommand());
	_commands.push_back(new JoinCommand());
	_commands.push_back(new PartCommand());
	_commands.push_back(new WhoCommand());
	_commands.push_back(new KickCommand());
	_commands.push_back(new ListCommand());
	_commands.push_back(new PassCommand());
	_commands.push_back(new ErrorCommand());
	_commands.push_back(new QuitCommand());
	_commands.push_back(new UserCommand());
	_commands.push_back(new NoticeCommand());
	_commands.push_back(new PrivateMessageCommand());
}

Invoker::~Invoker() {
	vector<Command*>::iterator it;

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
			} catch(string message) {
				sender->getReply(message);
			}
			break;
		}
	}
}

bool	Invoker::isCommand(string data) {
	vector<Command*>::iterator it;

	for (it = _commands.begin(); it != _commands.end(); it++) {
		if ((*it)->getName() == data) {
			return true;
		}
	}
	return false;
}

deque<string> Invoker::dataToArgs(string data) {
	stringstream	ssMsg(data);
	string			av;
	deque<string>	arguments;

	while (getline(ssMsg, av, ' '))
	{
		av.erase(av.find_last_not_of(MSG_DELIMITER) + 1);
		if (!av.empty())
			arguments.push_back(av);
	}
	return arguments;
}

void	Invoker::processData(User *sender, string data) {
	deque<string> arguments = dataToArgs(data);

	if (!arguments.empty() && isCommand(arguments[0])) {
		cout << "@" << sender->getName() << " " << data; // delete
		processCommand(sender, arguments);
	}
}
