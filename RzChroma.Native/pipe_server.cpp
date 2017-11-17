#include "pipe_server.h"

namespace {
	const DWORD kPipeBlockSize = 1024;
}

PipeServer::PipeServer(const std::string name) :
	m_isListening(false),
	m_name(name),
	m_offerThread(std::bind(&PipeServer::OfferThread, this))
{
}

PipeServer::~PipeServer()
{
	if (m_isListening)
	{
		m_isListening = false;
		m_offerThread.join();
	}
}

const char* PipeServer::Name() const
{
	return m_name.c_str();
}

bool PipeServer::Flush()
{
	bool aggResult = true;

	for (size_t i = 0; i < m_handles.size(); ++i)
	{
		if (!m_handles[i]->Flush())
		{
			aggResult = false;
		}
	}

	return aggResult;
}

void PipeServer::Write(unsigned int dataSize, const unsigned char* data)
{
	if (m_handles.size() > 0)
	{
		for (size_t i = 0; i < m_handles.size(); ++i)
		{
			m_handles[i]->Write(dataSize, data);
		}
	}
}

void PipeServer::OfferThread()
{
	m_isListening = true;
	while (m_isListening)
	{
		auto hnd = CreateNamedPipe(
			m_name.c_str(),
			PIPE_ACCESS_OUTBOUND,
			PIPE_TYPE_MESSAGE,
			PIPE_UNLIMITED_INSTANCES,
			kPipeBlockSize,
			0,
			0,
			NULL);

		if (hnd != INVALID_HANDLE_VALUE)
		{
			// since we're not using overlapped io we can
			// do this synchronously and rely on blocking
			if (ConnectNamedPipe(hnd, NULL))
			{
				// cool we have a client
				m_handles.push_back(std::make_unique<BufferedPipe>(hnd, true));
			}
		}
	}
}