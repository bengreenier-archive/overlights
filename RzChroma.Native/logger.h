#pragma once

#include <fstream>
#include <map>
#include <string>

#include "constants.h"

#ifndef LOGGER_PATH
#define LOGGER_PATH ""
#endif

/// <summary>
/// Represents the different supported log levels
/// </summary>
enum LoggerLevel
{
	L_DEBUG,
	L_INFO,
	L_WARNING,
	L_ERROR
};

/// <summary>
/// Helper class for simple logging
/// </summary>
class Logger
{
public:
	/// <summary>
	/// A static logger instance to faciliate macro logging
	/// </summary>
	static Logger Instance;

	/// <summary>
	/// Default ctor
	/// </summary>
	/// <param name="path">the path to the log file</param>
	Logger(const std::string path = LOGGER_PATH);

	/// <summary>
	/// Default dtor
	/// </summary>
	~Logger();

	/// <summary>
	/// Gets a stream to log data to
	/// </summary>
	/// <param name="level">the level we wish to write data to</param>
	/// <returns>the stream</returns>
	std::ofstream& GetLogStream(LoggerLevel level);

protected:
	/// <summary>
	/// Converts a <see cref="LoggerLevel"/> to a string
	/// </summary>
	/// <param name="level">the level</param>
	/// <returns>string representation</returns>
	const char* LogLevelAsString(LoggerLevel level);

private:
	/// <summary>
	/// The underlying stream
	/// </summary>
	std::ofstream m_stream;
};

/// <summary>
/// Macro used for quick logging
/// </summary>
/// <param name="sev">the <see cref="LoggerLevel"/> to log at</param>
/// <returns>a log stream to which data can be written</returns>
#define LOG(sev) Logger::Instance.GetLogStream(sev)