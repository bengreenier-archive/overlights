#include "logger.h"

#include <windows.h>

Logger Logger::Instance;

Logger::Logger(const std::string path)
{
	std::string processedPath;
	
	if (path.empty())
	{
		char modName[MAX_PATH];
		if (0 != GetModuleFileNameA(NULL, modName, MAX_PATH))
		{
			auto wrappedModName = std::string(modName);
			processedPath = wrappedModName.substr(wrappedModName.find_last_of("\\") + 1) + ".log";
		}
		else
		{
			processedPath = "Logger.log";
		}
	}
	else
	{
		processedPath = path;
	}

	m_stream = std::ofstream(processedPath, std::ios_base::app);
}

Logger::~Logger()
{
	m_stream.flush();
	m_stream.close();
}

std::ofstream& Logger::GetLogStream(LoggerLevel level)
{
	m_stream << "\r\n[" << LogLevelAsString(level) << "] ";

	return m_stream;
}

const char* Logger::LogLevelAsString(LoggerLevel level)
{
	switch (level)
	{
	case LoggerLevel::L_DEBUG:
		return "DEBUG";
	case LoggerLevel::L_ERROR:
		return "ERROR";
	case LoggerLevel::L_INFO:
		return "INFO";
	case LoggerLevel::L_WARNING:
		return "WARNING";
	default:
		return "UNKNOWN";
	}
}