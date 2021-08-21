#ifndef Command_hpp
# define Command_hpp

class Command;

# include <iostream>
# include <string>
# include <deque>
# include "../Server/Server.hpp"
# include "../User/User.hpp"
# include "../Utils/ircserv.hpp"

using namespace std;

class Command {
	protected:
		string _name;

	public:
		Command(string name);
		virtual ~Command();
		string getName();

		virtual void execute(Server* server, User* user, deque<string> args);
};

#endif
