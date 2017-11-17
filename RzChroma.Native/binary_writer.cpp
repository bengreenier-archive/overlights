#include "binary_writer.h"

namespace
{
	template<typename TType>
	void ToBytes(TType value, unsigned char* bytes, int offset = 0)
	{
		const size_t size = sizeof(TType);

		for (auto i = 0; i < size; ++i)
		{
			// bytes[0] = (value >> (8 * 0)) & 0xFF
			bytes[offset + i] = (value >> (8 * i)) & 0xFF;
		}
	}
}

BinaryWriter::BinaryWriter(IOutboundPipe* pipe) :
	m_pipe(pipe)
{
}

BinaryWriter::~BinaryWriter()
{
}

void BinaryWriter::WriteInt(int value, bool flush)
{
	unsigned char converted[sizeof(int)];
	ToBytes<int>(value, converted);

	m_pipe->Write(sizeof(int), converted);

	if (flush)
	{
		m_pipe->Flush();
	}
}

void BinaryWriter::WriteByte(unsigned char value, bool flush)
{
	m_pipe->Write(sizeof(unsigned char), new unsigned char[1]{value});

	if (flush)
	{
		m_pipe->Flush();
	}
}

void BinaryWriter::WriteString(const std::string value, bool flush)
{
	// + 1 to include \0
	m_pipe->Write(value.length() + 1 , (unsigned char*)value.c_str());

	if (flush)
	{
		m_pipe->Flush();
	}
}