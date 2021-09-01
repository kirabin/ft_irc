#include "LeaveCommand.hpp"

LeaveCommand::LeaveCommand() {
	_name = "PART";
	_description = "PART #channel - leave channel";
}

LeaveCommand::~LeaveCommand() {}

void LeaveCommand::execute() {

	if (!_sender->didRegister())
		throw ERR_RESTRICTED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);
	if (!_server->getChannel(_args[0]))
		throw ERR_NOSUCHCHANNEL(_args[0]);
	if (_sender->getChannel() != _server->getChannel(_args[0]))
		throw ERR_NOTONCHANNEL(_args[0]);

	_server->getChannel(_args[0])->sendMessageToChannel(_sender, "left channel", this->_name);
	_sender->removeUserFromChannel();
	_sender->setChannel(nullptr);

}
