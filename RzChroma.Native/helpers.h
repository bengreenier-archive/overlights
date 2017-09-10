#pragma once

#include <string>

#include <windows.h>

namespace
{
	/// <summary>
	/// Returns the <c>GetLastError()</c> result as a message string
	/// <summary>
	/// <returns>the message string</returns>
	const char* GetLastErrorAsString()
	{
		//Get the error message, if any.
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return std::string().c_str(); //No error message has been recorded

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);

		return message.c_str();
	}
}