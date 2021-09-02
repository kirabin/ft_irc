#ifndef PartCommand_hpp
# define PartCommand_hpp
# include "../Command.hpp"

using namespace std;

class PartCommand: public Command {
	public:
		PartCommand();
		virtual ~PartCommand();
		void execute();
};

#endif
