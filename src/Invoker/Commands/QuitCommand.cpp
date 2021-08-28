#include "QuitCommand.hpp"

QuitCommand::QuitCommand() {
	_name = "QUIT";
	_description = "QUIT [ <Quit Message> ] — quit server [and leave a message]";
}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute() {
	// if (_args > 0) {
	// 	// TODO: print message somewhere
	// }
    _server->removeUser(_sender->getId());

}
