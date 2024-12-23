[![License:MIT](https://img.shields.io/badge/License-MIT-blue?style=plastic)](LICENSE)
[![C++ CI build](../../actions/workflows/build.yml/badge.svg)](../../actions/workflows/build.yml)

### syslog_cpp
Simple C++ syslog library to write to Linux syslog with streams.
Internally uses syslog.h

## <sub>Features</sub>

 - user log levels
 - use facilities
 - use tagging
 - copy entry to std::cout/std::cerr/std::clog

Features are activated using either subscript [] operators or << operators.
All features work with both, except tag name which only works with subscript []
operator.

### <sub>Log levels</sub>

 - EMERG
 - ALERT
 - CRITICAL (LOG_CRIT)
 - ERROR (LOG_ERR)
 - WARNING
 - NOTICE
 - INFO
 - DEBUG

### <sub>Facilities</sub>

 - KERN
 - USER
 - MAIL
 - NEWS
 - UUCP
 - DAEMON
 - AUTH
 - CRON
 - LPR
 - LOCAL0
 - LOCAL1
 - LOCAL2
 - LOCAL3
 - LOCAL4
 - LOCAL5
 - LOCAL6
 - LOCAL7

### <sub>Secondary write streams</sub>
syslog_cpp allows printing to one of these streams when writing
log entry to syslog:

 - COUT
 - CERR
 - CLOG

## <sub>Depencies</sub>

 - Linux
 - syslog.h


## <sub>Importing</sub>

 - import syslog_cpp as a submodule to directory syslog
 - include syslog_cpp's Makefile.inc in your Makefile
 - link with SYSLOG_OBJS

check Makefile of example program to see a sample.

Note: with default build system, you needs objs directory in your project's root, this is path
where all object files will be built.

## <sub>Example</sub>

Sample code demonstrating features is provided. Needs to be executed with user id
who is allowed to write to syslog (no read permission needed).
