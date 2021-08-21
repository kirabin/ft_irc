#ifndef Command_hpp
# define Command_hpp

class Command;

# include <iostream>
# include <string>
# include <deque>
# include "../Server/Server.Class.hpp"
# include "../User/User.Class.hpp"
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

class NickCommand: public Command {
    public:
        NickCommand(string name);
        virtual ~NickCommand();
        void execute(Server* server, User* user, deque<string> args);
};



class HelpCommand: public Command {

	public:
		HelpCommand(string name);
		virtual ~HelpCommand();
		void execute(Server* server, User* user, deque<string> args);
};

class JoinCommand: public Command {
	public:
		JoinCommand(string name);
		virtual ~JoinCommand();
		void execute(Server* server, User* user, deque<string> args);
};

class LeaveCommand: public Command {
	public:
		LeaveCommand(string name);
		virtual ~LeaveCommand();
		void execute(Server* server, User* user, deque<string> args);
};

class WhoCommand: public Command {
	public:
		WhoCommand(string name);
		virtual ~WhoCommand();
		void execute(Server* server, User* user, deque<string> args);
};

class KickCommand: public Command {
	public:
		KickCommand(string name);
		virtual ~KickCommand();
		void execute(Server* server, User* user, deque<string> args);
};

#endif
