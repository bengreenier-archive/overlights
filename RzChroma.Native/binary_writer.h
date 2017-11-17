#pragma once

#include <sstream>
#include "buffered_pipe.h"

class BinaryWriter
{
public:
	BinaryWriter(IOutboundPipe* pipe);
	~BinaryWriter();

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

private:
	IOutboundPipe* m_pipe;
};

