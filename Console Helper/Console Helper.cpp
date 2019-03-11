#include "pipe_helper.h"

int main()
{
	pipe console;

	console.set_ansi(true);
	console.set_locale("sv");
	console.set_name("472");

	if (console.locale()) {
		std::cout << "Successfully changed Locale" << std::endl;
	}
	else {
		std::cout << "Could not change Locale" << std::endl;
	}

	if (console.ansi()) {
		std::cout << "Successfully turned on ANSI codes" << std::endl;
	}
	else {
		std::cout << "Could not set up ANSI codes" << std::endl;
	}

	if (console.connect()) {
		std::cout << "Successfully connected to pipe" << std::endl;

		while (console.alive()) {
			std::cout << console.pipe_read();
		}
	}
}