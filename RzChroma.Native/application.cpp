#include "application.h"

Application::Application(std::string pipeName) :
	m_pipe(pipeName.c_str())
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

	// note: changes in order of the m_pipe writes requires changes to the csharp wrapper as well
	m_pipe.WriteInt(Application::DataType::Keyboard);

	if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_BREATHING)
	{
		ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE *)pParam;

		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_BREATHING);
		m_pipe.WriteInt(effect->Type);
		
		{
			auto color = effect->Color1;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_pipe.WriteByte(red);
			m_pipe.WriteByte(green);
			m_pipe.WriteByte(blue);
			m_pipe.WriteByte(alpha);
		}

		{
			auto color = effect->Color2;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_pipe.WriteByte(red);
			m_pipe.WriteByte(green);
			m_pipe.WriteByte(blue);
			m_pipe.WriteByte(alpha);
		}

		if (!m_pipe.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_CUSTOM)
	{
		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE *)pParam;

		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_CUSTOM);
		m_pipe.WriteInt(ChromaSDK::Keyboard::MAX_ROW);
		m_pipe.WriteInt(ChromaSDK::Keyboard::MAX_COLUMN);

		for (auto i = 0; i < ChromaSDK::Keyboard::MAX_ROW; ++i)
		{
			for (auto j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; ++j)
			{
				auto color = effect->Color[i][j];

				unsigned char blue = GetBValue(color);
				unsigned char green = GetGValue(color);
				unsigned char red = GetRValue(color);
				unsigned char alpha = (color >> 24) & 0xFF;

				m_pipe.WriteByte(red);
				m_pipe.WriteByte(green);
				m_pipe.WriteByte(blue);
				m_pipe.WriteByte(alpha);
			}
		}

		if (!m_pipe.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_CUSTOM_KEY)
	{
		ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::CUSTOM_KEY_EFFECT_TYPE *)pParam;
		
		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_CUSTOM_KEY);
		m_pipe.WriteInt(ChromaSDK::Keyboard::MAX_ROW);
		m_pipe.WriteInt(ChromaSDK::Keyboard::MAX_COLUMN);

		for (auto i = 0; i < ChromaSDK::Keyboard::MAX_ROW; ++i)
		{
			for (auto j = 0; j < ChromaSDK::Keyboard::MAX_COLUMN; ++j)
			{
				auto color = effect->Key[i][j];

				unsigned char blue = GetBValue(color);
				unsigned char green = GetGValue(color);
				unsigned char red = GetRValue(color);
				unsigned char alpha = (color >> 24) & 0xFF;

				m_pipe.WriteByte(red);
				m_pipe.WriteByte(green);
				m_pipe.WriteByte(blue);
				m_pipe.WriteByte(alpha);
			}
		}

		if (!m_pipe.Flush())
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
		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_NONE);

		if (!m_pipe.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_REACTIVE)
	{
		ChromaSDK::Keyboard::REACTIVE_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::REACTIVE_EFFECT_TYPE *)pParam;

		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_REACTIVE);
		m_pipe.WriteInt(effect->Duration);

		auto color = effect->Color;

		unsigned char blue = GetBValue(color);
		unsigned char green = GetGValue(color);
		unsigned char red = GetRValue(color);
		unsigned char alpha = (color >> 24) & 0xFF;

		m_pipe.WriteByte(red);
		m_pipe.WriteByte(green);
		m_pipe.WriteByte(blue);
		m_pipe.WriteByte(alpha);

		if (!m_pipe.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_SPECTRUMCYCLING)
	{
		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_SPECTRUMCYCLING);

		if (!m_pipe.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_STARLIGHT)
	{
		ChromaSDK::Keyboard::STARLIGHT_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::STARLIGHT_EFFECT_TYPE *)pParam;

		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_STARLIGHT);
		m_pipe.WriteInt(effect->Type);
		m_pipe.WriteInt(effect->Duration);

		{
			auto color = effect->Color1;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_pipe.WriteByte(red);
			m_pipe.WriteByte(green);
			m_pipe.WriteByte(blue);
			m_pipe.WriteByte(alpha);
		}

		{
			auto color = effect->Color2;

			unsigned char blue = GetBValue(color);
			unsigned char green = GetGValue(color);
			unsigned char red = GetRValue(color);
			unsigned char alpha = (color >> 24) & 0xFF;

			m_pipe.WriteByte(red);
			m_pipe.WriteByte(green);
			m_pipe.WriteByte(blue);
			m_pipe.WriteByte(alpha);
		}

		if (!m_pipe.Flush())
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

		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_STATIC);
		m_pipe.WriteByte(red);
		m_pipe.WriteByte(green);
		m_pipe.WriteByte(blue);
		m_pipe.WriteByte(alpha);

		if (!m_pipe.Flush())
		{
			return RZRESULT_INVALID;
		}
	}
	else if (Effect == ChromaSDK::Keyboard::EFFECT_TYPE::CHROMA_WAVE)
	{
		ChromaSDK::Keyboard::WAVE_EFFECT_TYPE *effect = (struct ChromaSDK::Keyboard::WAVE_EFFECT_TYPE *)pParam;
		m_pipe.WriteInt(ChromaSDK::Keyboard::CHROMA_WAVE);
		m_pipe.WriteInt(effect->Direction);

		if (!m_pipe.Flush())
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