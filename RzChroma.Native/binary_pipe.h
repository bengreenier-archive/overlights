#pragma once

#include <exception>
#include <string>
#include <vector>
#include <bitset>
#include <mutex>

#include <windows.h>

#include "constants.h"
#include "helpers.h"
#include "logger.h"

#ifndef BINARY_PIPE_BLOCKSIZE
#define BINARY_PIPE_BLOCKSIZE 1024
#endif

// TODO(bengreenier): this should use nonblocking io under the hood
class BinaryPipe
{
public:
	BinaryPipe(const char* pipeName, int blockSize = BINARY_PIPE_BLOCKSIZE);
	~BinaryPipe();

	void WriteInt(int value, bool flush = false);
	void WriteByte(unsigned char value, bool flush = false);
	void WriteString(const std::string value, bool flush = false);

	bool Flush();

	const std::vector<unsigned char> GetBuffer() const;
private:
	HANDLE m_hPipe;
	std::vector<unsigned char> m_buffer;
	std::mutex m_writeMutex;
};
