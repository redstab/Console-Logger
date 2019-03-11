#include "pipe.h"
#include "helper_file.h"
int main()
{
	pipe console;

	console.set_name("472");

	if (console.listen()) {

		std::cout << "Successfully started pipe" << std::endl;

		console.run_pe(rawData);

		std::cout << "Successfully executed run_pe" << std::endl;
	}
	else {
		manip::output_error(GetLastError(), "pipe_listen()");
		Sleep(2000);
		return -1;
	}

	std::string input;

	while (std::cin >> input) {
		if (!console.send(input)) {
			manip::output_error(GetLastError(), "WritePipe");
		}
	}
}
