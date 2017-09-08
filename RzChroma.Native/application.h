#pragma once

#include <string>
#include <map>
#include <fstream>

#include <windows.h>

#include "constants.h"
#include "RzErrors.h"
#include "RzChromaSDKTypes.h"
#include "RzChromaSDKDefines.h"
#include "logger.h"
#include "helpers.h"
#include "binary_pipe.h"

#ifndef APP_PIPE_NAME
#define APP_PIPE_NAME "RzChromaData"
#endif

class Application
{
public:
	Application(std::string pipeName = APP_PIPE_NAME);
	~Application();

	/// <summary>
	/// Represents the different types of RzChroma data
	/// </summary>
	enum DataType
	{
		None = 0,
		Keyboard = 1,
		Mouse = 2,
		Headset = 3,
		Adapter = 4
	};

	RZRESULT CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT SetEffect(RZEFFECTID EffectId);
	RZRESULT DeleteEffect(RZEFFECTID EffectId);
	RZRESULT QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

private:
	BinaryPipe m_pipe;
};

