#pragma once
#include "..\Library\manip.h"

class pipe{
public:
	pipe(){};
	pipe(std::string name, std::string c_locale,bool man_ansi);
	std::string pipe_read();
	
	bool connect();
	bool locale();
	bool ansi();
	bool alive(){return _alive;}

	void set_locale(std::string locale);
	void set_name(std::string name);
	void set_ansi(bool value);

private:
	HANDLE pipe_handle{};
	std::string pipe_name = R"(\\.\pipe\)";
	std::string _locale{};
	bool _ansi = false;
	bool _alive = true;
	bool _connect(std::string pipe_name);
};