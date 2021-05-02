#include <array>
#include <gtest/gtest.h>
#include <RawBufferHeaderOnly/RawBuffer.h>
#include "include/random.hpp"

namespace RawBufferTests
{
	TEST(Buffer, NewCreatedBufferIsEmpty)
	{
		const RawBuffer rawBuffer;
		
		EXPECT_EQ(rawBuffer.getSize(), 0);
	}

	TEST(Buffer, AddChar)
	{
		using Random = effolkronium::random_static;
		const char testChar = Random::get<char>();;

		RawBuffer rawBuffer;
		rawBuffer += testChar;
		
		EXPECT_EQ(rawBuffer.getInternalBuffer().at(0), static_cast<std::byte>(testChar));
	}

	TEST(Buffer, AddUnsignedChar)
	{
		using Random = effolkronium::random_static;
		const unsigned char testUnsignedChar = Random::get<unsigned char>();
		
		RawBuffer rawBuffer;
		rawBuffer += testUnsignedChar;
		
		EXPECT_EQ(rawBuffer.getInternalBuffer().at(0), static_cast<std::byte>(testUnsignedChar));
	}

	TEST(Buffer, AddVectorOfChar)
	{
		using Random = effolkronium::random_static;
		std::vector<char> vectorOfChar;
		const size_t numberOfElementsToBePushed = Random::get<unsigned short>();
		for(size_t i = 0; i < numberOfElementsToBePushed; i++)
		{
			vectorOfChar.push_back(Random::get<char>());
		}

		RawBuffer rawBuffer;
		rawBuffer += vectorOfChar;
		
		EXPECT_EQ(rawBuffer.getSize(), vectorOfChar.size());
		//EXPECT_TRUE(std::equal(vectorOfChar.begin(), vectorOfChar.end(), rawBuffer.getInternalBuffer().begin()));
		std::cout << "\nAddVectorOfChar test succeeded with " << vectorOfChar.size() << " elements.\n";
	}

	TEST(Buffer, AddArrayOfChar)
	{
		using Random = effolkronium::random_static;
		constexpr size_t arraySize = 6000;
		std::array<char, arraySize> arrayOfChar = {0};
		for (size_t i = 0; i < arraySize; i++)
		{
			arrayOfChar.at(i) = Random::get<char>();
		}
		
		RawBuffer rawBuffer;
		rawBuffer += arrayOfChar;

		EXPECT_EQ(rawBuffer.getSize(), arrayOfChar.size());
		//EXPECT_TRUE(std::equal(vectorOfChar.begin(), vectorOfChar.end(), rawBuffer.getInternalBuffer().begin()));
		std::cout << "\nAddArrayOfChar test succeeded with " << arrayOfChar.size() << " elements.\n";
	}

	TEST(Buffer, AddRawArrayOfChar)
	{
		using Random = effolkronium::random_static;
		constexpr size_t arraySize = 7000;
		char rawArrayOfChar[arraySize] = { 0 };
		for (char& i : rawArrayOfChar)
		{
			i = Random::get<char>();
		}

		RawBuffer rawBuffer;
		rawBuffer += rawArrayOfChar;
		
		EXPECT_EQ(rawBuffer.getSize(), arraySize);
		//EXPECT_TRUE(std::equal(rawBuffer.getInternalBuffer().begin(), rawBuffer.getInternalBuffer().end(), &rawArrayOfChar[0]));
		std::cout << "\nAddRawArrayOfChar test succeeded with " << arraySize << " elements.\n";
	}


	TEST(Buffer, AddArrayOfByte)
	{
		using Random = effolkronium::random_static;
		constexpr size_t arraySize = 6000;
		std::array<std::byte, arraySize> arrayOfByte{};
		for (size_t i = 0; i < arraySize; i++)
		{
			arrayOfByte.at(i) = static_cast<std::byte>(Random::get<unsigned char>());
		}

		RawBuffer rawBuffer;
		rawBuffer += arrayOfByte;

		EXPECT_EQ(rawBuffer.getSize(), arrayOfByte.size());
		for (size_t i = 0; i < rawBuffer.getSize(); i++)
		{
			EXPECT_EQ(rawBuffer.getInternalBuffer().at(i), arrayOfByte.at(i));
		}
		std::cout << "\nAddArrayOfByte test succeeded with " << arrayOfByte.size() << " elements.\n";
	}

	TEST(Buffer, AddRawArrayOfByte)
	{
		using Random = effolkronium::random_static;
		constexpr size_t arraySize = 7000;
		std::byte rawArrayOfByte[arraySize];
		for (std::byte& i : rawArrayOfByte)
		{
			i = static_cast<std::byte>(Random::get<unsigned char>());
		}

		RawBuffer rawBuffer;
		rawBuffer += rawArrayOfByte;

		EXPECT_EQ(rawBuffer.getSize(), arraySize);
		for (size_t i = 0; i < rawBuffer.getSize(); i++)
		{
			EXPECT_EQ(rawBuffer.getInternalBuffer().at(i), rawArrayOfByte[i]);
		}
		std::cout << "\nAddRawArrayOfByte test succeeded with " << arraySize << " elements.\n";
	}

	TEST(Buffer, AddAnotherBuffer)
	{
		using Random = effolkronium::random_static;

		RawBuffer rawBuffer;
		const size_t initialSize = Random::get<unsigned short>();;
		for (size_t i = 0; i < initialSize; i++)
		{
			rawBuffer += Random::get<unsigned char>();
		}

		RawBuffer otherRawBuffer;
		const size_t sizeOfOtherRawBuffer = Random::get<unsigned short>();;
		for (size_t i = 0; i < sizeOfOtherRawBuffer; i++)
		{
			otherRawBuffer += Random::get<unsigned char>();
		}

		rawBuffer += otherRawBuffer;
		

		EXPECT_EQ(rawBuffer.getSize(), initialSize + sizeOfOtherRawBuffer);
		for (size_t i = initialSize; i < rawBuffer.getSize(); i++)
		{
			EXPECT_EQ(rawBuffer.getInternalBuffer().at(i), otherRawBuffer.getInternalBuffer().at(i - initialSize));
		}
		std::cout << "\nAddAnotherBuffer test succeeded with " << initialSize + sizeOfOtherRawBuffer << " elements.\n";
	}
}