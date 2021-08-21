#ifndef EXECUTOR_CLASS_HPP
# define EXECUTOR_CLASS_HPP

class Executor;

# include "../Utils/ircserv.hpp"
# include "../Server/Server.Class.hpp"
# include "Command.hpp"

class Executor
{
	private:
		Server						*_server;
		User						*_sender;
		std::string					_msg;
		std::vector<std::string>	_argv;
		std::vector<Command*>		_commands;

		void			processCommand();

		void			help();
		void			nick();
		void			join();
		void			leave();
		void			who();
		void			kick();

		void			sendErrorReply(std::string info);
		void			clearArgv();

	public:
		Executor(Server *server);
		~Executor();

		void			setServer(Server *server);

		std::string		getMessage()const;
		User			*getSender()const;

		void			processData(User *sender, std::string msg);
};

#endif
