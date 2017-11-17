#include "application.h"

Application::Application(std::string pipeName) :
	m_pipeServer(pipeName.c_str()),
	m_binaryWriter(&m_pipeServer)
{
}

Application::~Application()
{
}

RZRESULT Application::CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	LOG(L_INFO) << __FUNCTION__ << ": " << Effect;

	// note: changes in order of the m_binaryWriter writes requires changes to the csharp wrapper as well
	m_binaryWriter.WriteInt(Application::DataType::Keyboard);

	if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_BREATHING)
	{
		ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE *)pParam;

		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_BREATHING);
		m_binaryWriter.WriteInt(effect->Type);
		
		{
			auto color = effect->Color1;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_binaryWriter.WriteByte(red);
			m_binaryWriter.WriteByte(green);
			m_binaryWriter.WriteByte(blue);
			m_binaryWriter.WriteByte(alpha);
		}

		{
			auto color = effect->Color2;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_binaryWriter.WriteByte(red);
			m_binaryWriter.WriteByte(green);
			m_binaryWriter.WriteByte(blue);
			m_binaryWriter.WriteByte(alpha);
		}

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_CUSTOM)
	{
		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE *)pParam;

		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_CUSTOM);
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::MAX_ROW);
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::MAX_COLUMN);

		for (auto i = 0; i < ChromaSDK::Keyboard::MAX_ROW; ++i)
		{
			for (auto j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; ++j)
			{
				auto color = effect->Color[i][j];

				unsigned char blue = GetBValue(color);
				unsigned char green = GetGValue(color);
				unsigned char red = GetRValue(color);
				unsigned char alpha = (color >> 24) & 0xFF;

				m_binaryWriter.WriteByte(red);
				m_binaryWriter.WriteByte(green);
				m_binaryWriter.WriteByte(blue);
				m_binaryWriter.WriteByte(alpha);
			}
		}

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_CUSTOM_KEY)
	{
		ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE *)pParam;
		
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY);
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::MAX_ROW);
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::MAX_COLUMN);

		for (auto i = 0; i < ChromaSDK::Keyboard::MAX_ROW; ++i)
		{
			for (auto j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; ++j)
			{
				auto color = effect->Key[i][j];

				unsigned char blue = GetBValue(color);
				unsigned char green = GetGValue(color);
				unsigned char red = GetRValue(color);
				unsigned char alpha = (color >> 24) & 0xFF;

				m_binaryWriter.WriteByte(red);
				m_binaryWriter.WriteByte(green);
				m_binaryWriter.WriteByte(blue);
				m_binaryWriter.WriteByte(alpha);
			}
		}

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_INVALID)
	{
		return RZRESULT_INVALID;
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_NONE)
	{
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_NONE);

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_REACTIVE)
	{
		ChromaSDK::Keyboard::REACTIVE_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::REACTIVE_EFFECT_TYPE *)pParam;

		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_REACTIVE);
		m_binaryWriter.WriteInt(effect->Duration);

		auto color = effect->Color;

		unsigned char blue = GetBValue(color);
		unsigned char green = GetGValue(color);
		unsigned char red = GetRValue(color);
		unsigned char alpha = (color >> 24) & 0xFF;

		m_binaryWriter.WriteByte(red);
		m_binaryWriter.WriteByte(green);
		m_binaryWriter.WriteByte(blue);
		m_binaryWriter.WriteByte(alpha);

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_SPECTRUMCYCLING)
	{
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_SPECTRUMCYCLING);

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_STARLIGHT)
	{
		ChromaSDK::Keyboard::STARLIGHT_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::STARLIGHT_EFFECT_TYPE *)pParam;

		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_STARLIGHT);
		m_binaryWriter.WriteInt(effect->Type);
		m_binaryWriter.WriteInt(effect->Duration);

		{
			auto color = effect->Color1;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_binaryWriter.WriteByte(red);
			m_binaryWriter.WriteByte(green);
			m_binaryWriter.WriteByte(blue);
			m_binaryWriter.WriteByte(alpha);
		}

		{
			auto color = effect->Color2;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_binaryWriter.WriteByte(red);
			m_binaryWriter.WriteByte(green);
			m_binaryWriter.WriteByte(blue);
			m_binaryWriter.WriteByte(alpha);
		}

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_STATIC)
	{
		ChromaSDK::Keyboard::STATIC_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::STATIC_EFFECT_TYPE *)pParam;

		unsigned char blue = GetBValue(effect->Color);
		unsigned char green = GetGValue(effect->Color);
		unsigned char red = GetRValue(effect->Color);
		unsigned char alpha = (effect->Color >> 24) & 0xFF;

		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_STATIC);
		m_binaryWriter.WriteByte(red);
		m_binaryWriter.WriteByte(green);
		m_binaryWriter.WriteByte(blue);
		m_binaryWriter.WriteByte(alpha);

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_WAVE)
	{
		ChromaSDK::Keyboard::WAVE_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::WAVE_EFFECT_TYPE *)pParam;
		m_binaryWriter.WriteInt(ChromaSDK::Keyboard::CHROMA_WAVE);
		m_binaryWriter.WriteInt(effect->Direction);

		// since the binary writer is writing to the pipe server, now we force flush that data
		// as we've written a complete single message
		if (!m_pipeServer.Flush())
		{
			return RZRESULT_INVALID;
		}
	}

	return RZRESULT_SUCCESS;
}

RZRESULT Application::CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::SetEffect(RZEFFECTID EffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::DeleteEffect(RZEFFECTID EffectId)
{
	LOG(L_INFO) << __FUNCTION__;
	return RZRESULT_INVALID;
}

RZRESULT Application::QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo)
{
	LOG(L_INFO) << __FUNCTION__;

	// only support 2 devices, one mouse and one keyboard
	// as we extend this library to support more device types
	// we'll likely want to expand these conditions
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