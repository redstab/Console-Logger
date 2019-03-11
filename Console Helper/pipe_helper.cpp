#include "pipe_helper.h"

pipe::pipe(std::string name, std::string c_locale, bool man_ansi)
{
	pipe_name += name;
	_locale = c_locale;
	_ansi = man_ansi;

	if (manip::get_locale() != _locale)
	{

		manip::global_locale(_locale); // Set C localization to Swedish

		if (_ansi) {

			manip::enable_ansi(); // Enable ANSI escape codes

		}

	}
}

bool pipe::connect()
{
	return _connect(pipe_name);
}

bool pipe::locale()
{
	if (manip::get_locale() != _locale) {
		manip::global_locale(_locale);
		return true;
	}
	else {
		return false;
	}
}

bool pipe::ansi()
{
	if (_ansi) {
		manip::enable_ansi();
		return true;
	}
	else {
		return false;
	}
}

void pipe::set_locale(std::string locale)
{
	_locale = locale;
}

void pipe::set_name(std::string name)
{
	pipe_name += name;
}

void pipe::set_ansi(bool value)
{
	_ansi = value;
}

std::string pipe::pipe_read()
{
	char pipe_buffer[4096]{};

	unsigned long read_bytes = 0;

	if (!ReadFile(
		pipe_handle,
		&pipe_buffer,
		4096,
		&read_bytes,
		nullptr
	))
	{
		std::cout << std::endl;
		manip::output_error(GetLastError(), "ReadFile()");
		if(GetLastError() == 109){
			_alive = false;
		}
		Sleep(2000);
	}
	return std::string(pipe_buffer);
}

bool pipe::_connect(std::string pipe_name)
{
	while (true) {

		pipe_handle = CreateFileA(

			pipe_name.c_str(),
			GENERIC_READ,
			0,
			nullptr,
			OPEN_EXISTING,
			0,
			nullptr
		);
		// if its not invalid it must be valid -> breaking loop
		if (pipe_handle != INVALID_HANDLE_VALUE) {
			break;
		}
		
		// if any other error than pipe busy 
		if (GetLastError() != ERROR_PIPE_BUSY) {
			manip::output_error(GetLastError(), "_connect()");
			Sleep(100); // Not Busy wait 100 ms
		}
	}

	// Clear Screen after connect ANSI code
	// "[1J" (J)erase (1)above | "[H" Move cursor to upper left corner
	std::cout << "";//"\033[1J\033[H"; 

	return true;
}
