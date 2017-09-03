#include "application.h"

#define LOG(sev) Log(sev) << __FUNCTION__ << ": "

Application::Application(std::string pipeName) :
	m_log("RzChroma.log", std::ios_base::app)
{
	LOG(L_INFO) << "Allocating pipe: " << pipeName;

	m_hPipe = CreateNamedPipe(
		pipeName.c_str(),
		PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_MESSAGE,
		PIPE_UNLIMITED_INSTANCES,
		1024,
		0,
		0,
		NULL);

	if (m_hPipe == NULL || m_hPipe == INVALID_HANDLE_VALUE)
	{
		auto lastErr = GetLastErrorAsString();

		LOG(L_ERROR) << "Error: " << lastErr;
		
		throw std::exception(lastErr);
	}
}

Application::~Application()
{
	CloseHandle(m_hPipe);
	m_log.close();
}

RZRESULT Application::CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	Log(L_INFO) << __FUNCTION__;

	if (Effect == ChromaSDK::Keyboard::CHROMA_STATIC)
	{
		ChromaSDK::Keyboard::STATIC_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::STATIC_EFFECT_TYPE *)pParam;

		// TODO(bengreenier): bitshift better n00b

		unsigned char blue = GetBValue(effect->Color);
		unsigned char green = GetGValue(effect->Color);
		unsigned char red = GetRValue(effect->Color);
		unsigned char alpha = LOBYTE(effect->Color) >> 24;

		const int dataBufSize = (sizeof(int32_t) * 2) + (sizeof(char) * 4);

		// the CHROMA_STATIC impacts the entire keyboard - rather than building a map of all keys
		// we use the RZKEY_INVALID value to indicate all keys
		//
		// format: number of key data point(s), key, red, green, blue, alpha, next key, r, g, b, a, etc
		unsigned char dataBuf[dataBufSize] = {
			// note that (int32_t)1 needs to be fit into 1 byte chunks
			LOBYTE(1),
			LOBYTE(1) >> 8,
			LOBYTE(1) >> 16,
			LOBYTE(1) >> 24,
			// note that (int32_t)RZKEY_INVALID needs to be fit into 1 byte chunks
			LOBYTE((int32_t)ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID),
			LOBYTE((int32_t)ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID) >> 8,
			LOBYTE((int32_t)ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID) >> 16,
			LOBYTE((int32_t)ChromaSDK::Keyboard::RZKEY::RZKEY_INVALID) >> 24,
			red,
			green,
			blue,
			alpha
		};

		LOG(L_DEBUG) << "Writing " << dataBuf;

		DWORD cbBytes;
		BOOL cbRes = WriteFile(
			m_hPipe,
			dataBuf,
			dataBufSize,
			&cbBytes,
			NULL
		);

		if (!cbRes || cbBytes != dataBufSize)
		{
			LOG(L_ERROR) << "Failed to Write " << cbRes << " " << cbBytes;

			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::CHROMA_BREATHING)
	{
		ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE *)pParam;

		// TODO(bengreenier): write this, requires parser changes on the native side
	}

	return RZRESULT_SUCCESS;
}

RZRESULT Application::CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::SetEffect(RZEFFECTID EffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::DeleteEffect(RZEFFECTID EffectId)
{
	Log(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo)
{
	Log(L_INFO) << __FUNCTION__;

	if (DeviceId == ChromaSDK::BLACKWIDOW_CHROMA)
		DeviceInfo.DeviceType = ChromaSDK::DEVICE_INFO_TYPE::DeviceType::DEVICE_KEYBOARD;
	else if (DeviceId == ChromaSDK::DEATHADDER_CHROMA)
		DeviceInfo.DeviceType = ChromaSDK::DEVICE_INFO_TYPE::DeviceType::DEVICE_MOUSE;
	else
	{
		DeviceInfo.Connected = 0;
		return RZRESULT_SUCCESS;
	}

	DeviceInfo.Connected = 1;

	return RZRESULT_SUCCESS;
}

std::ofstream& Application::Log(LogLevel level)
{
	// each call to this method indicates a new log entry
	m_log << "\r\n";

	return m_log;
}

const char* Application::GetLastErrorAsString()
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