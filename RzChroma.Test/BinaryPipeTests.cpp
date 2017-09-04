#include "stdafx.h"
#include "CppUnitTest.h"

#include "binary_pipe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RzChromaTest
{		
	TEST_CLASS(BinaryPipeTests)
	{
	public:
		
		TEST_METHOD(IntSerializationSucceeds)
		{
			BinaryPipe pipe("\\\\.\\pipe\\nul");
			pipe.WriteInt(12);

			auto buffer = pipe.GetBuffer();
			auto bufferInt = (int*)buffer.data();

			Assert::AreEqual(12, *bufferInt);
		}

		TEST_METHOD(ByteSerializationSucceeds)
		{
			BinaryPipe pipe("\\\\.\\pipe\\nul");
			pipe.WriteByte('a');

			auto buffer = pipe.GetBuffer();
			auto bufferByte = (char*)buffer.data();

			Assert::AreEqual('a', *bufferByte);
		}

		TEST_METHOD(MultiByteSerializationSucceeds)
		{
			BinaryPipe pipe("\\\\.\\pipe\\nul");
			pipe.WriteByte('a');
			pipe.WriteByte('b');
			pipe.WriteByte(LOBYTE(1));

			auto buffer = pipe.GetBuffer();
			auto bufferByte = (char*)buffer.data();

			Assert::AreEqual('a', *bufferByte);
			++bufferByte;
			Assert::AreEqual('b', *bufferByte);
			++bufferByte;
			Assert::AreEqual(LOBYTE(1), (BYTE)*bufferByte);
		}

		TEST_METHOD(MultiTypeSerializationSucceeds)
		{
			BinaryPipe pipe("\\\\.\\pipe\\nul");
			pipe.WriteInt(12);
			pipe.WriteByte('a');
			pipe.WriteString("test");

			auto buffer = pipe.GetBuffer();
			auto bufferRaw = (unsigned char*)buffer.data();

			auto intVal = (int*)bufferRaw;
			++bufferRaw;
			++bufferRaw;
			++bufferRaw;
			++bufferRaw;
			auto byteVal = (char*)bufferRaw;
			++bufferRaw;
			auto strVal = (const char*)bufferRaw;

			Assert::AreEqual(12, *intVal);
			Assert::AreEqual('a', *byteVal);
			Assert::AreEqual("test", strVal);
		}
	};
}