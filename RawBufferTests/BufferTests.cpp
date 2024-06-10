#include <array>
#include <string>
#include <cstring>
#include <cstdio>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <RawBufferHeaderOnly/RawBuffer.h>
#include "include/random.hpp"

namespace RawBufferTests
{
    // @brief Fixture for RawBuffer tests
    class RawBufferFixture : public ::testing::Test
    {
    public:
        void SetUp() override
        {
            rawBuffer.clear();
        }

        RawBuffer rawBuffer;
    };

    // @brief Tests that a newly created buffer is empty.
    TEST_F(RawBufferFixture, Should_BeEmpty_When_NewlyCreated)
    {
        EXPECT_EQ(rawBuffer.size(), 0);
    }

    // @brief Tests adding a single byte to the buffer using the single byte constructor.
    TEST_F(RawBufferFixture, Should_AddSingleByte_When_UsingSingleByteConstructor)
    {
        const auto testByte = Random::get<std::byte>();
        const RawBuffer buffer(testByte);

        EXPECT_EQ(buffer.size(), 1);
        EXPECT_THAT(buffer, ::testing::ElementsAre(testByte));
    }

    // @brief Tests adding a single byte to the buffer using the single byte constructor.
    TEST_F(RawBufferFixture, Should_AddSingleChar_When_UsingSingleCharConstructor)
    {
        const auto testChar = Random::get<char>();
        const RawBuffer rawBuffer(testChar);

        EXPECT_EQ(rawBuffer.size(), 1);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAre(static_cast<RawBuffer::value_type>(testChar)));
    }

    // @brief Tests adding data from a container to the buffer using the container constructor.
    TEST_F(RawBufferFixture, Should_AddDataFromByteContainer_When_UsingContainerConstructor)
    {
        std::vector<std::byte> testData;
        const auto numberOfElementsToBePushed = static_cast<std::size_t>(Random::get<unsigned short>());
        testData.reserve(numberOfElementsToBePushed);

        std::ranges::generate(testData,
                              []() { return Random::get<std::byte>(); });

        const RawBuffer buffer(testData);

        EXPECT_EQ(buffer.size(), testData.size());
        EXPECT_THAT(buffer, ::testing::ElementsAreArray(testData));
    }

    // @brief Tests adding data from a container to the buffer using the container constructor.
    TEST_F(RawBufferFixture, Should_AddDataFromCharContainer_When_UsingContainerConstructor)
    {
        std::vector<char> testData;
        constexpr size_t numberOfElementsToBePushed = 350;
        testData.reserve(numberOfElementsToBePushed);

        std::ranges::generate(testData,
                              []() { return Random::get<char>(); });

        const RawBuffer rawBuffer(testData);

        EXPECT_EQ(rawBuffer.size(), testData.size());
        // Compare the content. The below test code is needed since vector holds char type and rawBuffer holds std::byte type.
        EXPECT_THAT(rawBuffer, ::testing::Pointwise(::testing::Truly([](const auto& elements) {
            return std::get<0>(elements) == static_cast<RawBuffer::value_type>(std::get<1>(elements));
        }), testData));
    }

    // @brief Tests adding data from a raw array to the buffer using the raw array constructor.
    TEST_F(RawBufferFixture, Should_AddDataFromRawByteArray_When_UsingRawArrayConstructor)
    {
        constexpr size_t arraySize = 800;
        std::byte rawArrayOfByte[arraySize];

        std::ranges::generate(rawArrayOfByte,
                             []() { return Random::get<std::byte>(); });

        const RawBuffer rawBuffer(rawArrayOfByte);

        EXPECT_EQ(rawBuffer.size(), arraySize);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAreArray(rawArrayOfByte));
    }

    // @brief Tests adding data from a raw array to the buffer using the raw array constructor.
    TEST_F(RawBufferFixture, Should_AddDataFromRawCharArray_When_UsingRawArrayConstructor)
    {
        constexpr size_t arraySize = 800;
        char rawArrayOfChar[arraySize];

        std::ranges::generate(rawArrayOfChar,
                             []() { return Random::get<char>(); });

        const RawBuffer rawBuffer(rawArrayOfChar);

        EXPECT_EQ(rawBuffer.size(), arraySize);
        // Compare the content. The below test code is needed since vector holds char type and rawBuffer holds std::byte type.
        EXPECT_THAT(rawBuffer, ::testing::Pointwise(::testing::Truly([](const auto& elements) {
            return std::get<0>(elements) == static_cast<RawBuffer::value_type>(std::get<1>(elements));
        }), rawArrayOfChar));
    }

    // @brief Tests the clear method of RawBuffer.
    TEST_F(RawBufferFixture, Should_ClearBuffer_When_ClearMethodCalled)
    {
        // Add some data to the buffer
        rawBuffer += static_cast<std::byte>(0x01);
        rawBuffer += static_cast<std::byte>(0x02);
        rawBuffer += static_cast<std::byte>(0x03);

        // Clear the buffer
        rawBuffer.clear();

        // Check if the buffer is empty
        EXPECT_EQ(rawBuffer.size(), 0);
    }

    // @brief Tests adding a single char to the buffer.
    TEST_F(RawBufferFixture, Should_AddChar_When_AddingSingleChar)
    {
        const char testChar = Random::get<char>();
        rawBuffer += testChar;

        EXPECT_EQ(rawBuffer.size(), 1);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAre(static_cast<RawBuffer::value_type>(testChar)));
    }

    // @brief Tests adding a single unsigned char to the buffer.
    TEST_F(RawBufferFixture, Should_AddUnsignedChar_When_AddingSingleUnsignedChar)
    {
        const unsigned char testUnsignedChar = Random::get<unsigned char>();
        rawBuffer += testUnsignedChar;

        EXPECT_EQ(rawBuffer.size(), 1);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAre(static_cast<RawBuffer::value_type>(testUnsignedChar)));
    }

    // @brief Tests adding a vector of chars to the buffer.
    TEST_F(RawBufferFixture, Should_AddVectorOfChar_When_AddingVectorOfChar)
    {
        std::vector<char> vectorOfChar;
        constexpr size_t numberOfElementsToBePushed = 487;
        vectorOfChar.reserve(numberOfElementsToBePushed); // Reserve space for efficiency

        std::ranges::generate(vectorOfChar,
                              []() { return Random::get<char>(); });

        rawBuffer += vectorOfChar;


        EXPECT_EQ(rawBuffer.size(), vectorOfChar.size());
        // Compare the content. The below test code is needed since vector holds char type and rawBuffer holds std::byte type.
        EXPECT_THAT(rawBuffer, ::testing::Pointwise(::testing::Truly([](const auto& elements) {
            return std::get<0>(elements) == static_cast<RawBuffer::value_type>(std::get<1>(elements));
        }), vectorOfChar));
    }

    // @brief Tests adding an array of chars to the buffer.
    TEST_F(RawBufferFixture, Should_AddArrayOfChar_When_AddingArrayOfChar)
    {
        constexpr size_t arraySize = 600;
        std::array<char, arraySize> arrayOfChar{};

        std::ranges::generate(arrayOfChar,
                              []() { return Random::get<char>(); });


        rawBuffer += arrayOfChar;


        EXPECT_EQ(rawBuffer.size(), arrayOfChar.size());
        // Compare the content. The below test code is needed since vector holds char type and rawBuffer holds std::byte type.
        EXPECT_THAT(rawBuffer, ::testing::Pointwise(::testing::Truly([](const auto& elements) {
            return std::get<0>(elements) == static_cast<RawBuffer::value_type>(std::get<1>(elements));
        }), arrayOfChar));
    }

    // @brief Tests adding a raw array of chars to the buffer.
    TEST_F(RawBufferFixture, Should_AddRawArrayOfChar_When_AddingRawArrayOfChar)
    {
        constexpr size_t arraySize = 700;
        char rawArrayOfChar[arraySize] = { 0 };

        std::ranges::generate(rawArrayOfChar,
                              []() { return Random::get<char>(); });


        rawBuffer += rawArrayOfChar;

        EXPECT_EQ(rawBuffer.size(), arraySize);
        // Compare the content. The below test code is needed since vector holds char type and rawBuffer holds std::byte type.
        EXPECT_THAT(rawBuffer, ::testing::Pointwise(::testing::Truly([](const auto& elements) {
            return std::get<0>(elements) == static_cast<RawBuffer::value_type>(std::get<1>(elements));
        }), rawArrayOfChar));
    }

    // @brief Tests adding a span of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddSpanOfByte_When_AddingSpanOfByte)
    {
        constexpr size_t spanSize = 200;
        std::array<std::byte, spanSize> array{};

        std::ranges::generate(array,
                              []() { return Random::get<std::byte>(); });


        const std::span<std::byte> span{array};
        rawBuffer += span;


        EXPECT_EQ(rawBuffer.size(), spanSize);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAreArray(array));
    }

    // @brief Tests adding an array of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddArrayOfByte_When_AddingArrayOfByte)
    {
        constexpr size_t arraySize = 600;
        std::array<std::byte, arraySize> arrayOfByte{};

        std::ranges::generate(arrayOfByte,
                             []() { return Random::get<std::byte>(); });


        rawBuffer += arrayOfByte;


        EXPECT_EQ(rawBuffer.size(), arrayOfByte.size());
        EXPECT_THAT(rawBuffer, ::testing::ElementsAreArray(arrayOfByte));
    }

    // @brief Tests adding a raw array of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddRawArrayOfByte_When_AddingRawArrayOfByte)
    {
        constexpr size_t arraySize = 800;
        std::byte rawArrayOfByte[arraySize];

        std::ranges::generate(rawArrayOfByte,
                             []() { return Random::get<std::byte>(); });


        rawBuffer += rawArrayOfByte;


        EXPECT_EQ(rawBuffer.size(), arraySize);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAreArray(rawArrayOfByte));
    }

    // @brief Tests adding the contents of another buffer to the buffer.
    TEST_F(RawBufferFixture, Should_AddContentsOfAnotherBuffer_When_AddingAnotherBuffer)
    {
        const auto initialSize = static_cast<size_t>(Random::get<unsigned short>());
        for (size_t i = 0; i < initialSize; i++)
        {
            rawBuffer += Random::get<unsigned char>();
        }
        std::vector<std::byte> initialBuffer{rawBuffer.begin(), rawBuffer.end()};

        RawBuffer otherRawBuffer;
        const auto sizeOfOtherRawBuffer = static_cast<size_t>(Random::get<unsigned short>());
        for (size_t i = 0; i < sizeOfOtherRawBuffer; i++)
        {
            otherRawBuffer += Random::get<unsigned char>();
        }

        rawBuffer += otherRawBuffer;

        EXPECT_EQ(rawBuffer.size(), initialSize + sizeOfOtherRawBuffer);
        std::vector<std::byte> expectedBuffer{};
        expectedBuffer.reserve(initialSize + sizeOfOtherRawBuffer);
        expectedBuffer.insert(expectedBuffer.end(), initialBuffer.begin(), initialBuffer.end());
        expectedBuffer.insert(expectedBuffer.end(), otherRawBuffer.begin(), otherRawBuffer.end());
        EXPECT_THAT(rawBuffer, ::testing::ElementsAreArray(expectedBuffer));
    }

    // @brief Tests the concatenation operator for RawBuffer.
    TEST_F(RawBufferFixture, Should_ConcatenateBuffers_When_ConcatenatingWithOperator)
    {
        RawBuffer buffer1;
        RawBuffer buffer2;
        constexpr size_t size1 = 1000;
        constexpr size_t size2 = 2000;
        for (size_t i = 0; i < size1; i++)
        {
            buffer1 += Random::get<unsigned char>();
        }
        for (size_t i = 0; i < size2; i++)
        {
            buffer2 += Random::get<unsigned char>();
        }

        const RawBuffer concatenatedBuffer = buffer1 + buffer2;

        EXPECT_EQ(concatenatedBuffer.size(), size1 + size2);
        RawBuffer::InternalBufferType expectedBuffer;
        expectedBuffer.reserve(size1 + size2);
        expectedBuffer.insert(expectedBuffer.end(), buffer1.begin(), buffer1.end());
        expectedBuffer.insert(expectedBuffer.end(), buffer2.begin(), buffer2.end());
        EXPECT_THAT(concatenatedBuffer, ::testing::ElementsAreArray(expectedBuffer));
    }

    // @brief Tests the range-based for loop for RawBuffer.
    TEST_F(RawBufferFixture, Should_UseRangeBasedForLoop_When_IteratingOverBuffer)
    {
        constexpr size_t bufferSize = 120;
        for (size_t elem = 0; elem < bufferSize; elem++)
        {
            rawBuffer += static_cast<std::byte>(elem);
        }

        size_t count = 0;
        for (const auto& byte : rawBuffer)
        {
            EXPECT_EQ(byte, static_cast<std::byte>(count++));
        }
        EXPECT_EQ(count, bufferSize);
    }

    // @brief Tests the equality operator for RawBuffer.
    TEST_F(RawBufferFixture, Should_CheckEquality_When_ComparingWithOperator)
    {
        RawBuffer buffer1;
        RawBuffer buffer2;
        constexpr size_t size = 100;
        for (size_t i = 0; i < size; i++)
        {
            const auto element = Random::get<std::byte>();
            buffer1 += element;
            buffer2 += element;
        }

        EXPECT_EQ(buffer1, buffer2);
    }

    // @brief Tests the operator<< function for RawBuffer.
    TEST_F(RawBufferFixture, Should_PrintBuffer_When_UsingOperator)
    {
        constexpr size_t size = 30;
        for (size_t i = 0; i < size; i++)
        {
            rawBuffer += Random::get<std::byte>();
        }

        // Create expected output using sprintf
        char expectedOutput[1000] = {0};
        for (const auto& data : rawBuffer) {
            char temp[20] = {0};
			std::snprintf(temp, sizeof(temp), "0x%02X\t", static_cast<unsigned int>(data));
        	std::strncat(expectedOutput, temp, sizeof(expectedOutput) - strlen(expectedOutput) - 1);
        }
		std::strncat(expectedOutput, "\n", sizeof(expectedOutput) - strlen(expectedOutput) - 1);

        testing::internal::CaptureStdout();

        std::cout << rawBuffer;

        const std::string actualOutput = testing::internal::GetCapturedStdout();
        EXPECT_EQ(actualOutput, expectedOutput);
    }

    // @brief Tests the to_string function for RawBuffer.
    TEST_F(RawBufferFixture, Should_ReturnStringRepresentation_When_UsingToString)
    {
        constexpr size_t size = 30;
        for (size_t i = 0; i < size; i++)
        {
            rawBuffer += Random::get<std::byte>();
        }

        const std::string header = "Header";
        // Create expected output using sprintf
        char expectedOutput[1000] = {0};
        std::snprintf(expectedOutput, sizeof(expectedOutput), "%s:\n", header.c_str());
        for (const auto& data : rawBuffer) {
            char temp[20] = {0};
            std::snprintf(temp, sizeof(temp), "0x%02X\t", static_cast<unsigned int>(data));
        	std::strncat(expectedOutput, temp, sizeof(expectedOutput) - strlen(expectedOutput) - 1);
        }
        std::strncat(expectedOutput, "\n", sizeof(expectedOutput) - strlen(expectedOutput) - 1);

        const std::string actualOutput = to_string(rawBuffer, header);
        EXPECT_EQ(actualOutput, expectedOutput);
    }
}
