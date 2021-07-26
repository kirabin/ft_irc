#include "iostream";

using std::cout;
using std::endl;

int main(int argc, char **argv) {
	if (argc < 2 || argc > 3) {
		cout << "There must be 2 or 3 arguments." << endl << "Example: [host:port_network:password_network] <port> <password>" << endl;
	} else if (argc == 3) {

	}
	return 0;
}
