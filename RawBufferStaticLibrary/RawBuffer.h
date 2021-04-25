#pragma once

#include <concepts>
#include <vector>

template <typename T>
concept IsUnsignedChar = std::is_same<T, unsigned char>::value;

template <typename T>
concept IsChar = std::is_same<T, char>::value;

template <typename  T>
concept OneByteData = sizeof(T) == 1;

class RawBuffer
{
public:
	inline RawBuffer();
	
	inline void operator+=(OneByteData auto data);
	
	inline void operator+=(const RawBuffer& otherBuffer);
	
	template<typename T> requires OneByteData<T>
	inline void operator+=(const std::vector<T>& vector);
	
	void add(OneByteData auto data);
	
	[[nodiscard]] inline const auto& getInternalBuffer() const;
	
	[[nodiscard]] inline size_t getBufferCapacity() const;
	
	[[nodiscard]] inline size_t getSize() const;

private:
	static constexpr size_t  INITIAL_SIZE_OF_BUFFER = 128;
	
	std::vector<std::byte> buffer;
};

inline RawBuffer::RawBuffer()
{
	buffer.reserve(INITIAL_SIZE_OF_BUFFER);
}


const auto& RawBuffer::getInternalBuffer() const
{
	return buffer;
}

size_t RawBuffer::getBufferCapacity() const
{
	return buffer.capacity();
}

size_t RawBuffer::getSize() const
{
	return buffer.size();
}

void RawBuffer::operator+=(const RawBuffer& otherBuffer)
{
	buffer.insert(buffer.end(), otherBuffer.getInternalBuffer().begin(), otherBuffer.getInternalBuffer().end());
}

template <typename T> requires OneByteData<T>
void RawBuffer::operator+=(const std::vector<T>& vector)
{
	buffer.insert(buffer.end(), vector.begin(), vector.end());
}

void RawBuffer::operator+=(OneByteData auto data)
{
	add(data);
}

void RawBuffer::add(OneByteData auto data)
{
	std::cout << "Size: " << sizeof(data) << std::endl;
	buffer.push_back(static_cast<std::byte>(data));
}
