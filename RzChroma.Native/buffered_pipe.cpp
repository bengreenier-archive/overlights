#include "buffered_pipe.h"

BufferedPipe::BufferedPipe(HANDLE nativeHandle, bool closeOnDestroy) :
	m_pipeHandle(nativeHandle),
	m_closeOnDestroy(closeOnDestroy)
{
	FILE_NAME_INFO nameInfo;
	
	// if this fails, we just will have an empty name (nbd, atm)
	if (GetFileInformationByHandleEx(nativeHandle, FILE_INFO_BY_HANDLE_CLASS::FileNameInfo, &nameInfo, sizeof(nameInfo)))
	{
		std::wstring pipeName(nameInfo.FileName);

		m_pipeName = std::string(pipeName.begin(), pipeName.end());
	}
}

BufferedPipe::~BufferedPipe()
{
	if (m_closeOnDestroy)
	{
		// grab the mutex to ensure we aren't writing and destroying
		std::lock_guard<std::mutex> writeGuard(m_writeMutex);
		CloseHandle(m_pipeHandle);
	}
}

const char* BufferedPipe::Name() const
{
	return m_pipeName.c_str();
}

void BufferedPipe::Write(unsigned int dataSize, const unsigned char* data)
{
	// TODO(bengreenier): there is probably a better way to do this
	for (size_t i = 0; i < dataSize; ++i)
	{
		m_buffer.push_back(data[i]);
	}
}

bool BufferedPipe::Flush()
{
	std::lock_guard<std::mutex> writeGuard(m_writeMutex);

	DWORD cbBytes;
	BOOL bResult = WriteFile(
		m_pipeHandle,
		(LPCVOID)m_buffer.data(),
		(DWORD)m_buffer.size(),
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