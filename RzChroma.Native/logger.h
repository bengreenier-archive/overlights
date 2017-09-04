#pragma once

#include <fstream>
#include <map>
#include <string>

#include "constants.h"

#ifndef LOGGER_PATH
#define LOGGER_PATH ""
#endif

enum LoggerLevel
{
	L_DEBUG,
	L_INFO,
	L_WARNING,
	L_ERROR
};

class Logger
{
public:
	static Logger Instance;

	Logger(const std::string path = LOGGER_PATH);
	~Logger();

	std::ofstream& GetLogStream(LoggerLevel level);

protected:
	const char* LogLevelAsString(LoggerLevel);

private:
	std::ofstream m_stream;
};

#define LOG(sev) Logger::Instance.GetLogStream(sev)