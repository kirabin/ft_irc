#include "User.hpp"

User::User(string nickname) : _nickname(nickname) {}

void User::joinChannel(Channel channel) {}

void User::setNickname(string new_nickname) {
	this->_nickname = new_nickname;
}

string& User::getNickname() const {
	return this->_nickname;
}
