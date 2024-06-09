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
	RawBuffer();
	
	void operator+=(OneByteData auto data);
	
	void operator+=(const RawBuffer& otherBuffer);
	
	template<typename T> requires OneByteData<T>
	void operator+=(const std::vector<T>& vector);
	
	void add(OneByteData auto data);
	
	[[nodiscard]] inline const auto& getInternalBuffer() const;
	
	[[nodiscard]] inline size_t getBufferCapacity() const;
	
	[[nodiscard]] inline size_t size() const;

private:
	static constexpr size_t  INITIAL_SIZE_OF_BUFFER = 128;
	
	std::vector<std::byte> buffer;
};
