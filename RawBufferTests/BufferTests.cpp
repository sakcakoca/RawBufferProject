#include <array>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <RawBufferHeaderOnly/RawBuffer.h>
#include "include/random.hpp"

namespace RawBufferTests
{
    // @brief Fixture for RawBuffer tests
    class RawBufferFixture : public ::testing::Test
    {
    protected:
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
        const char testChar = effolkronium::random_static::get<char>();
        rawBuffer += testChar;

        EXPECT_EQ(rawBuffer.size(), 1);
        EXPECT_THAT(rawBuffer.getInternalBuffer(), ::testing::ElementsAre(static_cast<std::byte>(testChar)));
    }

    // @brief Tests adding a single unsigned char to the buffer.
    TEST_F(RawBufferFixture, Should_AddUnsignedChar_When_AddingSingleUnsignedChar)
    {
        const unsigned char testUnsignedChar = effolkronium::random_static::get<unsigned char>();
        rawBuffer += testUnsignedChar;

        EXPECT_EQ(rawBuffer.size(), 1);
        EXPECT_THAT(rawBuffer.getInternalBuffer(), ::testing::ElementsAre(static_cast<std::byte>(testUnsignedChar)));
    }

    // @brief Tests adding a vector of chars to the buffer.
    TEST_F(RawBufferFixture, Should_AddVectorOfChar_When_AddingVectorOfChar)
    {
        std::vector<char> vectorOfChar;
        const size_t numberOfElementsToBePushed = effolkronium::random_static::get<unsigned short>();
        vectorOfChar.reserve(numberOfElementsToBePushed); // Reserve space for efficiency

        std::ranges::generate(vectorOfChar,
                              []() { return effolkronium::random_static::get<char>(); });

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
                              []() { return effolkronium::random_static::get<char>(); });


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
                              []() { return effolkronium::random_static::get<char>(); });


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
                              []() { return static_cast<std::byte>(effolkronium::random_static::get<unsigned char>()); });


        const std::span<std::byte> span{array};
        rawBuffer += span;


        EXPECT_EQ(rawBuffer.size(), spanSize);
        EXPECT_THAT(rawBuffer.getInternalBuffer(), ::testing::ElementsAreArray(array));
    }

    // @brief Tests adding an array of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddArrayOfByte_When_AddingArrayOfByte)
    {
        constexpr size_t arraySize = 600;
        std::array<std::byte, arraySize> arrayOfByte{};

        std::ranges::generate(arrayOfByte,
                             []() { return static_cast<std::byte>(effolkronium::random_static::get<unsigned char>()); });


        rawBuffer += arrayOfByte;


        EXPECT_EQ(rawBuffer.size(), arrayOfByte.size());
        EXPECT_THAT(rawBuffer.getInternalBuffer(), ::testing::ElementsAreArray(arrayOfByte));
    }

    // @brief Tests adding a raw array of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddRawArrayOfByte_When_AddingRawArrayOfByte)
    {
        constexpr size_t arraySize = 800;
        std::byte rawArrayOfByte[arraySize];

        std::ranges::generate(rawArrayOfByte,
                             []() { return static_cast<std::byte>(effolkronium::random_static::get<unsigned char>()); });


        rawBuffer += rawArrayOfByte;


        EXPECT_EQ(rawBuffer.size(), arraySize);
        EXPECT_THAT(rawBuffer.getInternalBuffer(), ::testing::ElementsAreArray(rawArrayOfByte));
    }

    // @brief Tests adding the contents of another buffer to the buffer.
    TEST_F(RawBufferFixture, Should_AddContentsOfAnotherBuffer_When_AddingAnotherBuffer)
    {
        const size_t initialSize = effolkronium::random_static::get<unsigned short>();
        for (size_t i = 0; i < initialSize; i++)
        {
            rawBuffer += effolkronium::random_static::get<unsigned char>();
        }
        std::vector<std::byte> initialBuffer{rawBuffer.begin(), rawBuffer.end()};

        RawBuffer otherRawBuffer;
        const size_t sizeOfOtherRawBuffer = effolkronium::random_static::get<unsigned short>();
        for (size_t i = 0; i < sizeOfOtherRawBuffer; i++)
        {
            otherRawBuffer += effolkronium::random_static::get<unsigned char>();
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
            buffer1 += effolkronium::random_static::get<unsigned char>();
        }
        for (size_t i = 0; i < size2; i++)
        {
            buffer2 += effolkronium::random_static::get<unsigned char>();
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
        constexpr size_t bufferSize = 500;
        for (size_t i = 0; i < bufferSize; i++)
        {
            rawBuffer += static_cast<std::byte>(i);
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
            const auto element = static_cast<std::byte>(effolkronium::random_static::get<unsigned char>());
            buffer1 += element;
            buffer2 += element;
        }

        EXPECT_EQ(buffer1, buffer2);
    }
}
