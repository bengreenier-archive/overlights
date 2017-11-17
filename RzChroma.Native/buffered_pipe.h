#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <windows.h>

/// <summary>
/// Represents a pipe capable of outbound communication
/// </summary>
struct IOutboundPipe
{
public:
	virtual const char* Name() const = 0;

	virtual void Write(unsigned int dataSize, const unsigned char* data) = 0;
	virtual bool Flush() = 0;
};

/// <summary>
/// Represents a reliable pipe with buffering capabilities
/// <summary>
/// <remarks>
/// This pipe can be used for outbound communication, and will buffer
/// Data to be sent until <see cref="Flush()"/> is called
class BufferedPipe : public IOutboundPipe
{
public:
	BufferedPipe(HANDLE nativeHandle, bool closeOnDestroy = false);
	~BufferedPipe();

	virtual const char* Name() const override;

	virtual void Write(unsigned int dataSize, const unsigned char* data) override;
	virtual bool Flush() override;
protected:
	HANDLE m_pipeHandle;
	bool m_closeOnDestroy;
	std::string m_pipeName;
	std::mutex m_writeMutex;
	std::vector<unsigned char> m_buffer;
};