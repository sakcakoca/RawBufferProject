#pragma once

#include <concepts>
#include <span>
#include <vector>
#include <iterator>

/**
 * @brief Concept to ensure that the type T is one byte in size.
 */
template <typename T>
concept OneByteData = sizeof(T) == 1;

/**
 * @brief A class representing a buffer for raw byte data.
 */
class RawBuffer
{
public:
    using InternalBufferType = std::vector<std::byte>; ///<Type alias for the internal buffer type.
    using value_type = std::byte; ///< Type alias for value type used in iterators.
    using iterator = InternalBufferType::iterator; ///< Iterator type for mutable access.
    using const_iterator = InternalBufferType::const_iterator; ///< Iterator type for constant access.

    /**
     * @brief A nested class providing helper functions for RawBuffer.
     */
    class Helper;

    /**
     * @brief Default constructor for RawBuffer.
     * Initializes the buffer with a reserved size.
     */
    RawBuffer()
    {
        buffer.reserve(INITIAL_SIZE_OF_BUFFER);
    }

    /**
     * @brief Adds a single byte of data to the buffer.
     * @param data The data to be added.
     * @return Reference to the current RawBuffer object.
     */
    RawBuffer& operator+=(OneByteData auto data)
    {
        add(data);
        return *this;
    }

    /**
     * @brief Adds a single byte of data to the buffer.
     * @param data The data to be added.
     */
    void push_back(OneByteData auto data)
    {
        add(data);
    }

    /**
     * @brief Adds a container of one-byte data to the buffer.
     * @tparam T The type of the container.
     * @param container The container with data to be added.
     * @return Reference to the current RawBuffer object.
     */
    template <typename T>
    RawBuffer& operator+=(T container) requires OneByteData<typename decltype(std::span{ container })::value_type>
    {
        for (auto s = std::span{ container }; auto data : s)
        {
            add(data);
        }
        return *this;
    }

    /**
     * @brief Adds a C-style array of one-byte data to the buffer.
     * @tparam T The type of the array elements.
     * @tparam N The size of the array.
     * @param rawArray The array with data to be added.
     * @return Reference to the current RawBuffer object.
     */
    template <typename T, std::size_t N>
    RawBuffer& operator+=(T(& rawArray)[N]) requires OneByteData<T>
    {
        *this += std::span{ rawArray };
        return *this;
    }

    /**
     * @brief Adds the contents of another RawBuffer to this buffer.
     * @param otherBuffer Another RawBuffer object.
     * @return Reference to the current RawBuffer object.
     */
    RawBuffer& operator+=(const RawBuffer& otherBuffer)
    {
        *this += otherBuffer.getInternalBuffer();
        return *this;
    }

    /**
     * @brief Spaceship operator for comparing RawBuffer objects.
     * @param other The RawBuffer object to compare with.
     * @return A comparison result.
     */
    auto operator<=>(const RawBuffer&) const = default;

    /**
     * @brief Gets the internal buffer.
     * @return A constant reference to the internal buffer.
     */
    [[nodiscard]] const InternalBufferType& getInternalBuffer() const
    {
        return buffer;
    }

    /**
     * @brief Gets the capacity of the buffer.
     * @return The capacity of the buffer.
     */
    [[nodiscard]] size_t getBufferCapacity() const
    {
        return buffer.capacity();
    }

    /**
     * @brief Gets the current size of the buffer.
     * @return The size of the buffer.
     */
    [[nodiscard]] size_t size() const
    {
        return buffer.size();
    }

    /**
     * @brief Clears the content of the buffer.
     */
    void clear()
    {
        buffer.clear();
    }

    /**
     * @brief Returns an iterator to the beginning of the buffer.
     * @return An iterator to the beginning of the buffer.
     */
    iterator begin() {
        return buffer.begin();
    }

    /**
     * @brief Returns an iterator to the end of the buffer.
     * @return An iterator to the end of the buffer.
     */
    iterator end() {
        return buffer.end();
    }

    /**
     * @brief Returns a constant iterator to the beginning of the buffer.
     * @return A constant iterator to the beginning of the buffer.
     */
    const_iterator begin() const {
        return buffer.begin();
    }

    /**
     * @brief Returns a constant iterator to the end of the buffer.
     * @return A constant iterator to the end of the buffer.
     */
    const_iterator end() const {
        return buffer.end();
    }

private:
    static constexpr size_t INITIAL_SIZE_OF_BUFFER = 128; ///< Initial size of the buffer.

    InternalBufferType buffer; ///< Vector to store the raw byte data.

    /**
     * @brief Adds a single byte of data to the buffer.
     * @param data The data to be added.
     */
    void add(OneByteData auto data)
    {
        buffer.push_back(static_cast<std::byte>(data));
    }
};


/**
 * @brief A nested class providing helper functions for RawBuffer.
 */
class RawBuffer::Helper
{
public:
    /**
     * @brief Prints a single byte of data.
     * @param data The data to be printed.
     * @param header Optional header string to be printed before the data.
     */
    static void printOneByteData(OneByteData auto data, const std::string& header = "")
    {
        printf("\n%s: 0x%02hhX\n", header.c_str(), data);
    }

    /**
     * @brief Prints the contents of a RawBuffer.
     * @param rawBuffer The RawBuffer object to be printed.
     * @param header Optional header string to be printed before the buffer contents.
     */
    static void printBuffer(const RawBuffer& rawBuffer, const std::string& header = "")
    {
        printf("\n%s: ", header.c_str());
        for (auto data : rawBuffer.getInternalBuffer())
        {
            printf("0x%02hhX\t", data);
        }
    }
};
