SYSLOGCPP_DIR?=./syslog
INCLUDES += -I$(SYSLOGCPP_DIR)/include

SYSLOG_OBJS:= \
	objs/syslogcpp.o

objs/usage_validator.o: $(USAGECPP_DIR)/src/validator.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/syslogcpp.o: $(SYSLOGCPP_DIR)/src/syslog.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
