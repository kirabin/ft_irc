#ifndef HelpCommand_hpp
# define HelpCommand_hpp
# include "../Command.hpp"

using namespace std;

class HelpCommand: public Command {
	private:
		std::vector<Command*>& _commands;

	public:
		HelpCommand(std::vector<Command*>& commands);
		virtual ~HelpCommand();
		void execute();
};

#endif
