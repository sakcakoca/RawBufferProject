#include <iostream>
#include "RawBuffer.h"

RawBuffer::RawBuffer()
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

size_t RawBuffer::size() const
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