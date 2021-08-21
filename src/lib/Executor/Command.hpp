#ifndef Command_hpp
# define Command_hpp
# include <string>
# include <iostream>

using namespace std;

class Command {
	protected:
		string _name;

	public:
		Command(string name);
		virtual ~Command();
		string getName();

		virtual void execute();
};

class HelpCommand: public Command {

	public:
		HelpCommand(string name);
		virtual ~HelpCommand();
		void execute();
};

class NickCommand: public Command {
	public:
		NickCommand(string name);
		virtual ~NickCommand();
		void execute();
};

class JoinCommand: public Command {
	public:
		JoinCommand(string name);
		virtual ~JoinCommand();
		void execute();
};

class LeaveCommand: public Command {
	public:
		LeaveCommand(string name);
		virtual ~LeaveCommand();
		void execute();
};

class WhoCommand: public Command {
	public:
		WhoCommand(string name);
		virtual ~WhoCommand();
		void execute();
};

class KickCommand: public Command {
	public:
		KickCommand(string name);
		virtual ~KickCommand();
		void execute();
};

#endif
