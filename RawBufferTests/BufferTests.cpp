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
        for (size_t i = 0; i < numberOfElementsToBePushed; i++)
        {
            vectorOfChar.push_back(effolkronium::random_static::get<char>());
        }

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
        constexpr size_t arraySize = 6000;
        std::array<char, arraySize> arrayOfChar = {0};
        for (size_t i = 0; i < arraySize; i++)
        {
            arrayOfChar.at(i) = effolkronium::random_static::get<char>();
        }

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
        constexpr size_t arraySize = 7000;
        char rawArrayOfChar[arraySize] = { 0 };
        for (char& i : rawArrayOfChar)
        {
            i = effolkronium::random_static::get<char>();
        }

        rawBuffer += rawArrayOfChar;

        EXPECT_EQ(rawBuffer.size(), arraySize);
        // Compare the content. The below test code is needed since vector holds char type and rawBuffer holds std::byte type.
        EXPECT_THAT(rawBuffer, ::testing::Pointwise(::testing::Truly([](const auto& elements) {
            return std::get<0>(elements) == static_cast<RawBuffer::value_type>(std::get<1>(elements));
        }), rawArrayOfChar));
    }

    // @brief Tests adding an array of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddArrayOfByte_When_AddingArrayOfByte)
    {
        constexpr size_t arraySize = 6000;
        std::array<std::byte, arraySize> arrayOfByte{};
        for (size_t i = 0; i < arraySize; i++)
        {
            arrayOfByte.at(i) = static_cast<std::byte>(effolkronium::random_static::get<unsigned char>());
        }

        rawBuffer += arrayOfByte;

        EXPECT_EQ(rawBuffer.size(), arrayOfByte.size());
        EXPECT_THAT(rawBuffer.getInternalBuffer(), ::testing::ElementsAreArray(arrayOfByte));
    }

    // @brief Tests adding a raw array of bytes to the buffer.
    TEST_F(RawBufferFixture, Should_AddRawArrayOfByte_When_AddingRawArrayOfByte)
    {
        constexpr size_t arraySize = 7000;
        std::byte rawArrayOfByte[arraySize];
        for (std::byte& i : rawArrayOfByte)
        {
            i = static_cast<std::byte>(effolkronium::random_static::get<unsigned char>());
        }

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

        RawBuffer::InternalBufferType vector_to_compare{ rawBuffer.begin(), rawBuffer.end() };

        RawBuffer otherRawBuffer;
        const size_t sizeOfOtherRawBuffer = effolkronium::random_static::get<unsigned short>();
        for (size_t i = 0; i < sizeOfOtherRawBuffer; i++)
        {
            otherRawBuffer += effolkronium::random_static::get<unsigned char>();
        }

        rawBuffer += otherRawBuffer;
        vector_to_compare.insert(vector_to_compare.end(), otherRawBuffer.begin(), otherRawBuffer.end());

        EXPECT_EQ(rawBuffer.size(), initialSize + sizeOfOtherRawBuffer);
        EXPECT_THAT(rawBuffer, ::testing::ElementsAreArray(vector_to_compare));
    }
}
