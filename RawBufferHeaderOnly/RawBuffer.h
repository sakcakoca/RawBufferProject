#pragma once

#include <concepts>
#include <span>
#include <vector>
#include <iterator>
#include <format>

/**
 * @brief Concept to ensure that the type T is one byte in size.
 */
template <typename T>
concept OneByteData = sizeof(T) == 1;

template <typename T>
concept SpanConstructible = requires(T container) {
    std::span{container};
};

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
     * @brief Default constructor for RawBuffer.
     * Initializes the buffer with a reserved size.
     */
    RawBuffer()
    {
        buffer.reserve(INITIAL_SIZE_OF_BUFFER);
    }

    /**
     * @brief Constructor for initializing with a single byte of data.
     * @param data The single byte of data to initialize the buffer with.
     */
    explicit RawBuffer(OneByteData auto data) {
        buffer.reserve(INITIAL_SIZE_OF_BUFFER);
        *this += data;
    }

    /**
     * @brief Constructor for initializing with data from a container.
     * @tparam T The type of the container.
     * @param container The container with data to initialize the buffer with.
     */
    template <typename T>
    explicit RawBuffer(const T& container) requires OneByteData<typename decltype(std::span{ container })::value_type>
    {
        buffer.reserve(INITIAL_SIZE_OF_BUFFER);
        *this += container;
    }

    template <typename T, std::size_t N>
    explicit RawBuffer(T(& rawArray)[N]) requires OneByteData<T>
    {
        buffer.reserve(INITIAL_SIZE_OF_BUFFER);
        *this += rawArray;
    }

    /**
     * @brief Adds a single byte of data to the buffer.
     * @param data The data to be added.
     */
    void push_back(OneByteData auto data)
    {
        buffer.push_back(static_cast<std::byte>(data));
    }

    /**
     * @brief Clears the content of the buffer.
     */
    void clear()
    {
        buffer.clear();
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
     * @brief Gets the capacity of the buffer.
     * @return The capacity of the buffer.
     */
    [[nodiscard]] size_t capacity() const
    {
        return buffer.capacity();
    }

    /**
     * @brief Gets the internal buffer.
     * @return A constant reference to the internal buffer.
     */
    [[nodiscard]] const InternalBufferType& getInternalBuffer() const
    {
        return buffer;
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
    [[nodiscard]] const_iterator begin() const {
        return buffer.begin();
    }

    /**
     * @brief Returns a constant iterator to the end of the buffer.
     * @return A constant iterator to the end of the buffer.
     */
    [[nodiscard]] const_iterator end() const {
        return buffer.end();
    }

    /**
     * @brief Spaceship operator for comparing RawBuffer objects.
     * @param other The RawBuffer object to compare with.
     * @return A comparison result.
     */
    auto operator<=>(const RawBuffer& other) const = default;

private:
    static constexpr size_t INITIAL_SIZE_OF_BUFFER = 128; ///< Initial size of the buffer.
    InternalBufferType buffer; ///< Vector to store the raw byte data.
};


/**
 * @brief Adds a single byte of data to the buffer.
 * @param lhs The left-hand side RawBuffer.
 * @param data The data to be added.
 * @return Reference to the modified RawBuffer object.
 */
RawBuffer& operator+=(RawBuffer& lhs, OneByteData auto data)
{
    lhs.push_back(data);
    return lhs;
}

/**
 * @brief Adds a container of one-byte data to the buffer.
 * @param lhs The left-hand side RawBuffer.
 * @tparam ContainerT The type of the container.
 * @param container The container with data to be added.
 * @return Reference to the modified RawBuffer object.
 */
template <typename ContainerT>
RawBuffer& operator+=(RawBuffer& lhs, const ContainerT& container)
    requires OneByteData<typename ContainerT::value_type> && SpanConstructible<ContainerT>
{
    // Copy elements from the container to the RawBuffer
    std::transform(container.begin(), container.end(), std::back_inserter(lhs), [](typename ContainerT::value_type val) {
        return static_cast<std::byte>(val);
    });

    return lhs;
}

/**
 * @brief Adds a C-style array of one-byte data to the buffer.
 * @param lhs The left-hand side RawBuffer.
 * @tparam T The type of the array elements.
 * @tparam N The size of the array.
 * @param rawArray The array with data to be added.
 * @return Reference to the modified RawBuffer object.
 */
template <typename T, std::size_t N>
RawBuffer& operator+=(RawBuffer& lhs, T(& rawArray)[N]) requires OneByteData<T>
{
    lhs += std::span{ rawArray };
    return lhs;
}

/**
 * @brief Adds the contents of another RawBuffer to this buffer.
 * @param lhs The left-hand side RawBuffer.
 * @param rhs The right-hand side RawBuffer.
 * @return Reference to the modified left-hand side RawBuffer object.
 */
RawBuffer& operator+=(RawBuffer& lhs, const RawBuffer& rhs)
{
    lhs += rhs.getInternalBuffer();
    return lhs;
}

/**
 * @brief Concatenates two RawBuffer objects.
 * @param lhs The left-hand side RawBuffer.
 * @param rhs The right-hand side RawBuffer.
 * @return A new RawBuffer containing the concatenated data.
 */
RawBuffer operator+(const RawBuffer& lhs, const RawBuffer& rhs)
{
    RawBuffer result;
    result += lhs.getInternalBuffer();
    result += rhs.getInternalBuffer();
    return result;
}

/**
 * @brief Overload the operator<< for RawBuffer.
 * @param os The output stream to write to.
 * @param rawBuffer The RawBuffer object to be written.
 * @return std::ostream& A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const RawBuffer& rawBuffer)
{
    for (auto data : rawBuffer.getInternalBuffer())
    {
        os << std::format("0x{:02X}\t", static_cast<unsigned int>(data));
    }
    os << '\n';
    return os;
}

/**
 * @brief Define the to_string function for RawBuffer.
 * @param rawBuffer The RawBuffer object to convert to string.
 * @param header Optional header string to be included in the output.
 * @return std::string A string representation of the RawBuffer object.
 */
std::string to_string(const RawBuffer& rawBuffer, const std::string& header = "")
{
    std::stringstream ss;
    if(!header.empty())
    {
        ss << header << ":\n";
    }
    ss << rawBuffer;
    return ss.str();
}