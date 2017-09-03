#pragma once

#include <windows.h>
#include <string>
#include <map>
#include <fstream>

#include "RzErrors.h"
#include "RzChromaSDKTypes.h"
#include "RzChromaSDKDefines.h"

class Application
{
public:
	Application(std::string pipeName = "RzChromaData");
	~Application();

	RZRESULT CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
	RZRESULT SetEffect(RZEFFECTID EffectId);
	RZRESULT DeleteEffect(RZEFFECTID EffectId);
	RZRESULT QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

	enum LogLevel
	{
		L_DEBUG,
		L_INFO,
		L_WARNING,
		L_ERROR
	};

	std::ofstream& Log(LogLevel level = L_INFO);
	const char* GetLastErrorAsString();
private:
	HANDLE m_hPipe;
	std::ofstream m_log;
};

