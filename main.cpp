#include <iostream>
#include "syslog.hpp"

int main(int argc, char **argv) {

	std::cout << "syslog test" << std::endl;

	syslog::info << "info message" << std::endl;
	syslog::error << "error message" << std::endl;

	syslog::info["tag"][syslog::AUTH][syslog::COUT] << "this is written to syslog and to generic output stream, facility is set to auth and this is also tagged with name tag" << std::endl;
	syslog::info << syslog::COUT << "this is another way to dual output to syslog and to screen" << std::endl;
	syslog::info << "my message";
	std::cout << "currently buffered message: " << syslog::info << std::endl;
	syslog::info.erase();
	syslog::info << "we just erased our previously buffered message" << std::endl;
	syslog::debug[syslog::COUT] << "this is ignored, because initially debug level is disabled" << std::endl;
	std::cout << "syslog debug level is " << ( syslog::debug ? "enabled" : "disabled" ) << " - enabling it now.." << std::endl;
	syslog::debug = true;
	std::cout << "now syslog's debug level is " << ( syslog::debug ? "enabled" : "disabled" ) << std::endl;
	syslog::debug[syslog::COUT] << "this is written to debug level after debug was enabled" << std::endl;

	std::cout << "\nall options, such as tag, facility and message copying, are reset with either reset, or by flushing of entry" << std::endl;

	return 0;

}
