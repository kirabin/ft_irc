#include "Command.hpp"

// Private Messages command
// Notice command

Command::Command() : _name(""), _description(""), _server(NULL), _sender(NULL) {}

Command::~Command() {}

string Command::getName() const {
	return _name;
}

string Command::getDescription() const {
	return _description;
}

void Command::setSender(User* sender) {
	_sender = sender;
}

void Command::setServer(Server* server) {
	_server = server;
}

void Command::setArgs(deque<string> args) {
	_args = args;
}

std::string Command::makeString() {

    std::string tmp;
    for (size_t i  = 0; i <= _args.size(); i++)
    {
        if (i == 0 && _server->getUser(_args[i]) == nullptr)
        {
            tmp = this->_args[i] ;
        }
        else if (_server->getUser(_args[i]) != nullptr)
        {
           ;
        }
        else
        {
            if (tmp.empty())
            {
                tmp =  this->_args[i] ;
            }
           else
            {
                tmp = tmp +  " " + this->_args[i] ;
            }
        }
    }
    tmp.erase(tmp.find_last_not_of("\n\r") + 1);
    return tmp;
}
