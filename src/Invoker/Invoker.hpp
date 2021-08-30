#ifndef Invoker_CLASS_HPP
# define Invoker_CLASS_HPP

class Invoker;

# include "Command.hpp"
# include "../Utils/ircserv.hpp"
# include "../Server/Server.hpp"
# include "../User/User.hpp"
# include <deque>
# include <vector>
# include <string>

using std::vector;
using std::string;
using std::deque;

class Invoker
{
	private:
		Server*				_server;
		vector<Command*>	_commands;

	public:
		Invoker(Server* server);
		virtual ~Invoker();

		void			processData(User* sender, string msg);
		void			processCommand(User* sender, deque<string> arguments);
		bool			isCommand(string data);
		deque<string>	dataToArgs(string data);
};

#endif
