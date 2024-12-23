#pragma once

#include <string>
#include <ostream>
#include <streambuf>

namespace syslog {

	enum COPY {
		COUT, CERR, CLOG, NONE
	};

	enum PRI {
		EMERG, ALERT, CRITICAL, ERROR, WARNING, NOTICE, INFO, DEBUG
	};

	enum FACILITY {
		KERN, USER, MAIL, NEWS, UUCP, DAEMON, AUTH, CRON, LPR,
		LOCAL0, LOCAL1, LOCAL2, LOCAL3, LOCAL4, LOCAL5, LOCAL6, LOCAL7
	};

	struct logger : std::basic_streambuf<char, std::char_traits<char>>, public std::ostream {

		using int_type = std::basic_streambuf<char>::int_type;
		using traits_type = std::basic_streambuf<char>::traits_type;

		private:
			PRI _pri;
			COPY _copy = syslog::COPY::NONE;
			FACILITY _fac = syslog::FACILITY::USER;
			std::string _name;
			void print_copy();

		protected:
			std::string _buf;
			int_type overflow(int_type ch);
			int sync();

		public:

			void erase();
			size_t size();
			bool empty();

			logger& operator =(const std::nullptr_t& n);
			logger& operator [](const std::string& name);
			logger& operator [](const syslog::COPY& copy_to);
			logger& operator [](const syslog::FACILITY& facility);

			logger& operator <<(const std::ostream* c);
			logger& operator <<(const syslog::COPY& copy_to);
			logger& operator <<(const syslog::FACILITY& facility);
			logger& operator <<(const std::nullptr_t& n);

			logger(const syslog::PRI& pri) : std::ostream(this), _pri(pri) {}

			friend std::ostream& operator <<(std::ostream& os, const logger& l);
	};

	extern logger emerg;
	extern logger alert;
	extern logger critical;
	extern logger error;
	extern logger warning;
	extern logger notice;
	extern logger info;
	extern logger debug;

	std::ostream& operator <<(std::ostream& os, const syslog::logger& l);
}
