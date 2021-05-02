#pragma once

#include <concepts>
#include <span>
#include <vector>

template <typename  T>
concept OneByteData = sizeof(T) == 1;


class RawBuffer
{
public:
	class Helper;
	
	RawBuffer();
	
	RawBuffer& operator+=(OneByteData auto data);
	
	template <typename T>
	RawBuffer& operator+=(T container) requires OneByteData<typename decltype(std::span{ container })::element_type>;

	template <typename T, std::size_t N>
	RawBuffer& operator+=(T(&rawArray)[N]);

	RawBuffer& operator+=(const RawBuffer& otherBuffer);

	friend bool operator==(const RawBuffer& lhs, const RawBuffer& rhs);

	friend bool operator!=(const RawBuffer& lhs, const RawBuffer& rhs);
	
	[[nodiscard]] inline const auto& getInternalBuffer() const;
	
	[[nodiscard]] inline size_t getBufferCapacity() const;
	
	[[nodiscard]] inline size_t getSize() const;


private:
	static constexpr size_t  INITIAL_SIZE_OF_BUFFER = 128;
	
	std::vector<std::byte> buffer;

	void add(OneByteData auto data);
};


inline RawBuffer::RawBuffer()
{
	buffer.reserve(INITIAL_SIZE_OF_BUFFER);
}


inline const auto& RawBuffer::getInternalBuffer() const
{
	return buffer;
}

inline size_t RawBuffer::getBufferCapacity() const
{
	return buffer.capacity();
}

inline size_t RawBuffer::getSize() const
{
	return buffer.size();
}

template <typename T>
RawBuffer& RawBuffer::operator+=(T container) requires OneByteData<typename decltype(std::span{ container })::element_type >
{
	for (auto data : std::span{container})
	{
		add(data);
	}

	return *this;
}

template <typename T, std::size_t N>
RawBuffer& RawBuffer::operator+=(T(& rawArray)[N])
{
	*this += std::span{ rawArray };
	
	return *this;
}

inline RawBuffer& RawBuffer::operator+=(const RawBuffer& otherBuffer)
{
	*this += otherBuffer.getInternalBuffer();
	return *this;
}

inline RawBuffer& RawBuffer::operator+=(OneByteData auto data)
{
	add(data);
	
	return *this;
}

inline bool operator==(const RawBuffer& lhs, const RawBuffer& rhs)
{
	return lhs.buffer == rhs.buffer;
}

inline bool operator!=(const RawBuffer& lhs, const RawBuffer& rhs)
{
	return !(lhs == rhs);
}


inline void RawBuffer::add(OneByteData auto data)
{
	buffer.push_back(static_cast<std::byte>(data));
}

class RawBuffer::Helper
{
public:
	static void printOneByteData(OneByteData auto data, const std::string& header = "")
	{
		printf("\n%s: 0x%02hhX\n", header.c_str(), data);
	}

	static void printBuffer(const RawBuffer& rawBuffer, const std::string& header = "")
	{
		printf("\n%s: ", header.c_str());
		
		for (auto data : rawBuffer.getInternalBuffer())
		{
			printf("0x%02hhX\t", data);
		}
	}
};