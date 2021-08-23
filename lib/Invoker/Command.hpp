#ifndef Command_hpp
# define Command_hpp

class Command;

# include <iostream>
# include <string>
# include <deque>
# include <vector>
# include "../Server/Server.hpp"
# include "../User/User.hpp"
# include "../Utils/ircserv.hpp"

using namespace std;

class Command {
	protected:
		string _name;
		string _description;
		Server *_server;
		User *_sender;
		deque<string> _args;

	public:
		Command();
		virtual ~Command();

		string getName() const;
		string getDescription() const;
		
		void setSender(User* sender);
		void setServer(Server* server);
		void setArgs(deque<string> args);

		virtual void execute() = 0;
};

#endif
