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
/// <summary>
/// Provides an abstraction for writing binary data to a named pipe
/// </summary>
class BinaryPipe
{
public:
	/// <summary>
	/// Default ctor
	/// </summary>
	/// <param name="pipeName">the name of the pipe to write to</param>
	/// <param name="blockSize">the data block size the pipe operates at</param>
	BinaryPipe(const char* pipeName, int blockSize = BINARY_PIPE_BLOCKSIZE);

	/// <summary>
	/// Default dtor
	/// </summary>
	~BinaryPipe();

	/// <summary>
	/// Write an int to the pipe
	/// </summary>
	/// <param name="value">value to write</param>
	/// <param name="flush">indicates if we should immediately flush the data to the pipe</param>
	void WriteInt(int value, bool flush = false);

	/// <summary>
	/// Write a byte to the pipe
	/// </summary>
	/// <param name="value">value to write</param>
	/// <param name="flush">indicates if we should immediately flush the data to the pipe</param>
	void WriteByte(unsigned char value, bool flush = false);

	/// <summary>
	/// Write a string to the pipe
	/// </summary>
	/// <param name="value">value to write</param>
	/// <param name="flush">indicates if we should immediately flush the data to the pipe</param>
	void WriteString(const std::string value, bool flush = false);

	/// <summary>
	/// Writes buffered data to the underlying pipe
	/// </summary>
	/// <remarks>
	/// The expectation is that callers will trigger this after a number of logically related writes
	/// </remarks>
	/// <returns>an indicator of success or failure</returns>
	bool Flush();

	/// <summary>
	/// Gets the underlying buffer
	/// <summary>
	/// <returns>the underlying buffer</returns>
	const std::vector<unsigned char> GetBuffer() const;
private:
	/// <summary>
	/// Pointer to the underlying named pipe handle
	/// </summary>
	HANDLE m_hPipe;

	/// <summary>
	/// The underlying buffer
	/// </summary>
	std::vector<unsigned char> m_buffer;

	/// <summary>
	/// Mutex used to ensure only a single <see cref="Flush()"/> call occurs at once
	/// </summary>
	std::mutex m_writeMutex;
};
