#include <gtest/gtest.h>
#include <RawBufferHeaderOnly/RawBuffer.h>


TEST(Buffer, NewCreatedBufferIsEmpty)
{
	const RawBuffer rawBuffer;
	EXPECT_EQ(rawBuffer.getSize(), 0);
}