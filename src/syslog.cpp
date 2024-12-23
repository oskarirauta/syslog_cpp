#include <iostream>
namespace csyslog {
	#include <syslog.h>
}

#include "syslog.hpp"

syslog::logger syslog::emerg(syslog::PRI::EMERG);
syslog::logger syslog::alert(syslog::PRI::ALERT);
syslog::logger syslog::critical(syslog::PRI::CRITICAL);
syslog::logger syslog::error(syslog::PRI::ERROR);
syslog::logger syslog::warning(syslog::PRI::WARNING);
syslog::logger syslog::notice(syslog::PRI::NOTICE);
syslog::logger syslog::info(syslog::PRI::INFO);
syslog::logger syslog::debug(syslog::PRI::DEBUG);

static int priority_to_int(const syslog::PRI& pri) {

        switch ( pri ) {
                case syslog::EMERG: return LOG_EMERG;
                case syslog::ALERT: return LOG_ALERT;
                case syslog::CRITICAL: return LOG_CRIT;
                case syslog::ERROR: return LOG_ERR;
                case syslog::WARNING: return LOG_WARNING;
                case syslog::NOTICE: return LOG_NOTICE;
                case syslog::INFO: return LOG_INFO;
                case syslog::DEBUG: return LOG_DEBUG;
        }
        return LOG_DEBUG;
}

static int facility_to_int(const syslog::FACILITY& fac) {

	switch ( fac ) {
		case syslog::KERN: return LOG_KERN;
		case syslog::USER: return LOG_USER;
		case syslog::MAIL: return LOG_MAIL;
		case syslog::NEWS: return LOG_NEWS;
		case syslog::UUCP: return LOG_UUCP;
		case syslog::DAEMON: return LOG_DAEMON;
		case syslog::AUTH: return LOG_AUTH;
		case syslog::CRON: return LOG_CRON;
		case syslog::LPR: return LOG_LPR;
		case syslog::LOCAL0: return LOG_LOCAL0;
		case syslog::LOCAL1: return LOG_LOCAL1;
		case syslog::LOCAL2: return LOG_LOCAL2;
		case syslog::LOCAL3: return LOG_LOCAL3;
		case syslog::LOCAL4: return LOG_LOCAL4;
		case syslog::LOCAL5: return LOG_LOCAL5;
		case syslog::LOCAL6: return LOG_LOCAL6;
		case syslog::LOCAL7: return LOG_LOCAL7;
	}
	return LOG_USER;
}

int syslog::logger::sync() {

	if ( !this -> _buf.empty()) {

		if ( this -> _copy != syslog::COPY::NONE )
			this -> print_copy();

		csyslog::openlog(this -> _name.c_str(), 0, ( facility_to_int(this -> _fac) | priority_to_int(this -> _pri)));
		csyslog::syslog(priority_to_int(this -> _pri), "%s", this -> _buf.c_str());
		csyslog::closelog();
		this -> erase();
	}

	return 0;
}

syslog::logger::int_type syslog::logger::overflow(syslog::logger::int_type ch) {

	if ( ch == traits_type::eof())
		this -> sync();
	else this -> _buf += static_cast<char>(ch);

	return ch;
}

void syslog::logger::print_copy() {

	if ( this -> _copy == syslog::COPY::NONE )
		return;

	std::string s = this -> _buf;
	if ( !s.empty() && s.back() == '\n' )
		s.pop_back(); // remove std::endl \n - we use std::endl when we print this

	if ( s.empty())
		return;

	switch ( this -> _copy ) {
		case syslog::COPY::NONE: break; // just to avoid unnecessary compile time warning
		case syslog::COPY::COUT: std::cout << s << std::endl;; break;
		case syslog::COPY::CERR: std::cerr << s << std::endl; break;
		case syslog::COPY::CLOG: std::clog << s << std::endl; break;
	}
}

void syslog::logger::erase() {

	this -> _buf.erase();
	this -> _name.erase();
	this -> _copy = syslog::COPY::NONE;
	this -> _fac = syslog::FACILITY::USER;
}

size_t syslog::logger::size() {

	return this -> _buf.size();
}

bool syslog::logger::empty() {

	return this -> _buf.empty();
}

syslog::logger& syslog::logger::operator =(const std::nullptr_t& n) {

	if ( n == nullptr )
		this -> erase();
	return *this;
}

syslog::logger& syslog::logger::operator [](const std::string& name) {

	if ( name.empty())
		this -> _name.erase();
	else this -> _name = name;

	return *this;
}

syslog::logger& syslog::logger::operator [](const syslog::COPY& copy_to) {
	this -> _copy = copy_to;
	return *this;
}

syslog::logger& syslog::logger::operator [](const syslog::FACILITY& facility) {
	this -> _fac = facility;
	return *this;
}

syslog::logger& syslog::logger::operator <<(const std::ostream* c) {

	if ( c == &std::cout ) this -> _copy = syslog::COUT;
	else if ( c == &std::cerr ) this -> _copy = syslog::CERR;
	else if ( c == &std::clog ) this -> _copy = syslog::CLOG;
	else this -> _copy = syslog::NONE;

	return *this;
}

syslog::logger& syslog::logger::operator <<(const syslog::COPY& copy_to) {
	this -> _copy = copy_to;
	return *this;
}

syslog::logger& syslog::logger::operator <<(const syslog::FACILITY& facility) {
	this -> _fac = facility;
	return *this;
}

syslog::logger& syslog::logger::operator <<(const std::nullptr_t& n) {

	if ( n == nullptr )
		this -> _buf += "nullptr";
	return *this;
}

std::ostream& syslog::operator <<(std::ostream& os, const syslog::logger& l) {

	std::string s(l._buf);

	if ( !s.empty() && s.back() == '\n' )
		s.pop_back();

	if ( !s.empty())
		os << s;

	return os;
}
