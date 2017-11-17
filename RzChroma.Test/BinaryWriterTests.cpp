#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector>

#include "binary_writer.h"
#include "buffered_pipe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RzChromaTest
{		
	TEST_CLASS(BinaryWriterTests)
	{
	public:
		
		class MockPipe : public IOutboundPipe
		{
		public:
			virtual const char* Name() const override { return "MOCK"; }

			virtual void Write(unsigned int dataSize, const unsigned char* data) override { for (auto i = 0; i < dataSize; ++i) Data.push_back(data[i]); }
			virtual bool Flush() override { return FlushReturnValue; }

			std::vector<unsigned char> Data;
			bool FlushReturnValue;
		};

		MockPipe pipe;

		TEST_METHOD(IntSerializationSucceeds)
		{
			BinaryWriter writer(&pipe);
			writer.WriteInt(12);

			auto bufferInt = (int*)pipe.Data.data();
			Assert::AreEqual(12, *bufferInt);
		}

		TEST_METHOD(ByteSerializationSucceeds)
		{
			BinaryWriter writer(&pipe);
			writer.WriteByte('a');

			auto bufferByte = (char*)pipe.Data.data();

			Assert::AreEqual('a', *bufferByte);
		}

		TEST_METHOD(MultiByteSerializationSucceeds)
		{
			BinaryWriter writer(&pipe);
			writer.WriteByte('a');
			writer.WriteByte('b');
			writer.WriteByte(LOBYTE(1));

			auto bufferByte = (char*)pipe.Data.data();

			Assert::AreEqual('a', *bufferByte);
			++bufferByte;
			Assert::AreEqual('b', *bufferByte);
			++bufferByte;
			Assert::AreEqual(LOBYTE(1), (BYTE)*bufferByte);
		}

		TEST_METHOD(MultiTypeSerializationSucceeds)
		{
			BinaryWriter writer(&pipe);
			writer.WriteInt(12);
			writer.WriteByte('a');
			writer.WriteString("test");

			auto bufferRaw = (unsigned char*)pipe.Data.data();

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