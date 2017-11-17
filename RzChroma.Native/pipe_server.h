#pragma once

#include <string>
#include <thread>
#include <vector>
#include <windows.h>

#include "buffered_pipe.h"


class PipeServer : public IOutboundPipe
{
public:
	PipeServer(const std::string name);
	~PipeServer();

	virtual const char* Name() const override;
	virtual void Write(unsigned int dataSize, const unsigned char* data) override;
	virtual bool Flush() override;

private:
	void OfferThread();

	volatile bool m_isListening;
	std::string m_name;
	std::thread m_offerThread;
	std::vector<std::unique_ptr<BufferedPipe>> m_handles;
};

