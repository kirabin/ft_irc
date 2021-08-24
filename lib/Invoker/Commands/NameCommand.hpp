#ifndef NameCommand_hpp
# define NameCommand_hpp
# include "../Command.hpp"

using namespace std;

class NameCommand: public Command {
	public:
		NameCommand();
		virtual ~NameCommand();
		void execute();
};

#endif
