#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "application.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RzChromaTest
{
	TEST_CLASS(ApplicationTests)
	{
		const char* subkeyPath = "RzChroma.Test";
		const char* subkeyName = "Enabled";
		const int subkeyEnabled = 1;
		const int subkeyDisabled = 0;

		TEST_METHOD_INITIALIZE(Init)
		{
			RegDeleteKeyA(HKEY_CURRENT_USER, subkeyPath);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			RegDeleteKeyA(HKEY_CURRENT_USER, subkeyPath);
		}

		TEST_METHOD(ApplicationIsEnabledSucceeds)
		{
			RegSetKeyValueA(HKEY_CURRENT_USER, subkeyPath, subkeyName, REG_DWORD, &subkeyEnabled, sizeof(subkeyEnabled));

			Application app("\\\\.\\pipe\\nul", subkeyPath, subkeyName);

			Assert::IsTrue(app.IsEnabled());

			RegSetKeyValueA(HKEY_CURRENT_USER, subkeyPath, subkeyName, REG_DWORD, &subkeyDisabled, sizeof(subkeyDisabled));

			Assert::IsFalse(app.IsEnabled());
		}
	};
}