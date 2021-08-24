#ifndef PassCommand_hpp
# define PassCommand_hpp
# include "../Command.hpp"

using namespace std;

class PassCommand: public Command {
	public:
		PassCommand();
		virtual ~PassCommand();
		void execute();
};

#endif
