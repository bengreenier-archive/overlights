#include "binary_pipe.h"

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

BinaryPipe::BinaryPipe(const char* pipeName, int blockSize)
{
	m_hPipe = CreateNamedPipe(
		pipeName,
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,
		blockSize,
		0,
		0,
		NULL);

	if (m_hPipe == NULL || m_hPipe == INVALID_HANDLE_VALUE)
	{
		auto lastErr = GetLastErrorAsString();

		throw std::exception(lastErr);
	}
}

BinaryPipe::~BinaryPipe()
{
	if (m_hPipe != NULL && m_hPipe != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hPipe);
	}
}

void BinaryPipe::WriteInt(int value, bool flush)
{
	unsigned char converted[sizeof(int)];
	ToBytes<int>(value, converted);

	for (auto i = 0; i < sizeof(int); ++i)
	{
		m_buffer.push_back(converted[i]);
	}

	if (flush)
	{
		Flush();
	}
}

void BinaryPipe::WriteByte(unsigned char value, bool flush)
{
	m_buffer.push_back(value);

	if (flush)
	{
		Flush();
	}
}

void BinaryPipe::WriteString(const std::string value, bool flush)
{
	for (auto i = 0; i < value.length(); i++)
	{
		m_buffer.push_back(value[i]);
	}

	m_buffer.push_back('\0');

	if (flush)
	{
		Flush();
	}
}

bool BinaryPipe::Flush()
{
	std::lock_guard<std::mutex> writeGuard(m_writeMutex);

	LOG(L_DEBUG) << "Flushing data(" << m_buffer.size() << ")";

	DWORD cbBytes;
	BOOL bResult = WriteFile(
		m_hPipe,
		(LPCVOID) m_buffer.data(),
		(DWORD) m_buffer.size(),
		&cbBytes,
		NULL
	);

	if (bResult && cbBytes == m_buffer.size())
	{
		m_buffer.clear();
		return true;
	}
	else if (cbBytes != m_buffer.size())
	{
		// erase as much as we sent
		m_buffer.erase(m_buffer.begin(), m_buffer.begin() + cbBytes);
	}

	return false;
}

const std::vector<unsigned char> BinaryPipe::GetBuffer() const
{
	return m_buffer;
}
