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

/// <summary>
/// The RzChroma application logic class
/// </summary>
/// <remarks>
/// This class houses the core functionality of the module
/// </remarks>
class Application
{
public:
	/// <summary>
	/// Default ctor
	/// </summary>
	/// <param name="pipeName">the name of a named pipe to which data will be written</param>
	Application(std::string pipeName = APP_PIPE_NAME);

	/// <summary>
	/// Default dtor
	/// </summary>
	~Application();

	/// <summary>
	/// Represents the different types of RzChroma data that can be transmitted
	/// </summary>
	/// <remarks>
	/// All data sent must be prefixed with one of these identifiers so the receiver can id it
	/// </remarks>
	enum DataType
	{
		None = 0,
		Keyboard = 1,
		Mouse = 2,
		Headset = 3,
		Adapter = 4
	};

	/// <summary>
	/// Implements the ChromaSDK interface for creating visual lighting effects
	/// </summary>
	/// <param name="DeviceId">the device id for which this effect is created</param>
	/// <param name="Effect">the type of the effect to create</param>
	/// <param name="pParam">pointer to the effect data</param>
	/// <param name="pEffectId">pointer to the effect id</param>
	/// <returns>operation status indicator</returns>
	RZRESULT CreateEffect(RZDEVICEID DeviceId, ChromaSDK::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for creating keyboard visual lighting effects
	/// </summary>
	/// <param name="Effect">the type of the effect to create</param>
	/// <param name="pParam">pointer to the effect data</param>
	/// <param name="pEffectId">pointer to the effect id</param>
	/// <returns>operation status indicator</returns>
	RZRESULT CreateKeyboardEffect(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for creating headset visual lighting effects
	/// </summary>
	/// <param name="Effect">the type of the effect to create</param>
	/// <param name="pParam">pointer to the effect data</param>
	/// <param name="pEffectId">pointer to the effect id</param>
	/// <returns>operation status indicator</returns>

	RZRESULT CreateHeadsetEffect(ChromaSDK::Headset::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for creating mousepad visual lighting effects
	/// </summary>
	/// <param name="Effect">the type of the effect to create</param>
	/// <param name="pParam">pointer to the effect data</param>
	/// <param name="pEffectId">pointer to the effect id</param>
	/// <returns>operation status indicator</returns>

	RZRESULT CreateMousepadEffect(ChromaSDK::Mousepad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for creating mouse visual lighting effects
	/// </summary>
	/// <param name="Effect">the type of the effect to create</param>
	/// <param name="pParam">pointer to the effect data</param>
	/// <param name="pEffectId">pointer to the effect id</param>
	/// <returns>operation status indicator</returns>

	RZRESULT CreateMouseEffect(ChromaSDK::Mouse::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for creating keypad visual lighting effects
	/// </summary>
	/// <param name="Effect">the type of the effect to create</param>
	/// <param name="pParam">pointer to the effect data</param>
	/// <param name="pEffectId">pointer to the effect id</param>
	/// <returns>operation status indicator</returns>

	RZRESULT CreateKeypadEffect(ChromaSDK::Keypad::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for enabling visual lighting effects
	/// </summary>
	/// <param name="EffectId">the effect id</param>
	/// <returns>operation status indicator</returns>
	RZRESULT SetEffect(RZEFFECTID EffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for disabling visual lighting effects
	/// </summary>
	/// <param name="EffectId">the effect id</param>
	/// <returns>operation status indicator</returns>
	RZRESULT DeleteEffect(RZEFFECTID EffectId);

	/// <summary>
	/// Implements the ChromaSDK interface for determining system hardware capabilities
	/// </summary>
	/// <param name="DeviceId">the device id for which we wish to get information</param>
	/// <param name="DeviceInfo">object representing the information</param>
	/// <returns>operation status indicator</returns>
	RZRESULT QueryDevice(RZDEVICEID DeviceId, ChromaSDK::DEVICE_INFO_TYPE &DeviceInfo);

private:

	/// <summary>
	/// Internal <see cref="BinaryPipe"/> instance used for communication
	/// </summary>
	BinaryPipe m_pipe;
};

