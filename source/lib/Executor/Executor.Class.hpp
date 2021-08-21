#ifndef EXECUTOR_CLASS_HPP
# define EXECUTOR_CLASS_HPP

class Executor;

# include "Command.hpp"
# include "../Utils/ircserv.hpp"
# include "../Server/Server.Class.hpp"
# include "../User/User.Class.hpp"
# include <deque>
# include <vector>
# include <string>

using namespace std;

class Executor
{
	private:
		Server						*_server;
		User						*_sender;
		std::vector<Command*>		_commands;

		// void			help();
		// void			nick();
		// void			join();
		// void			leave();
		// void			who();
		// void			kick();

		void			sendErrorReply(std::string info);

	public:
		Executor(Server *server);
		~Executor();

		void			processData(User *sender, std::string msg);
		void			processCommand(User *sender, deque<string> arguments);
};

#endif
