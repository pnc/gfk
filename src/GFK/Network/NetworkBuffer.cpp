#include <GFK/Network/SocketHeader.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/BytePacker.hpp>

namespace gfk
{

NetworkBuffer::NetworkBuffer()
{
	
}

NetworkBuffer::~NetworkBuffer()
{

}

int NetworkBuffer::GetBufferCount()
{
	return bufferCounter;
}

unsigned char* NetworkBuffer::GetDataBuffer()
{
	return dataBuffer;
}

void NetworkBuffer::WriteSignedByte(signed char c)
{
	dataBuffer[bufferCounter] = c;
	bufferCounter++;
}

void NetworkBuffer::WriteUnsignedByte(unsigned char c)
{
	dataBuffer[bufferCounter] = c;
	bufferCounter++;
}

void NetworkBuffer::WriteSignedInt16(signed short int i)
{
	i = htons(i);
	dataBuffer[bufferCounter]     = (i & 0xff00) >> 8;
	dataBuffer[bufferCounter + 1] = i & 0x00ff;
	bufferCounter += 2;
}

void NetworkBuffer::WriteUnsignedInt16(unsigned short int i)
{
	i = htons(i);
	dataBuffer[bufferCounter]     = (i & 0xff00) >> 8;
	dataBuffer[bufferCounter + 1] = i & 0x00ff;
	bufferCounter += 2;
}

void NetworkBuffer::WriteSignedInt32(signed int i)
{
	i = htonl(i);
	dataBuffer[bufferCounter]     = (i & 0xff000000) >> 24;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff0000) >> 16;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff00) >> 8;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff);
	bufferCounter += 4;
}

void NetworkBuffer::WriteUnsignedInt32(unsigned int i)
{
	i = htonl(i);
	dataBuffer[bufferCounter]     = (i & 0xff000000) >> 24;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff0000) >> 16;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff00) >> 8;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff);
	bufferCounter += 4;
}

void NetworkBuffer::WriteSignedInt64(signed long int i)
{
	i = BytePacker::htonll(i);
	dataBuffer[bufferCounter]     = (i & 0xff00000000000000) >> 56;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff000000000000) >> 48;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff0000000000) >> 40;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff00000000) >> 32;
	dataBuffer[bufferCounter + 4] = (i & 0x00000000ff000000) >> 24;
	dataBuffer[bufferCounter + 5] = (i & 0x0000000000ff0000) >> 16;
	dataBuffer[bufferCounter + 6] = (i & 0x000000000000ff00) >> 8;
	dataBuffer[bufferCounter + 7] = (i & 0x00000000000000ff);
	bufferCounter += 8;

}

void NetworkBuffer::WriteUnsignedInt64(unsigned long int i)
{
	i = BytePacker::htonll(i);
	dataBuffer[bufferCounter]     = (i & 0xff00000000000000) >> 56;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff000000000000) >> 48;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff0000000000) >> 40;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff00000000) >> 32;
	dataBuffer[bufferCounter + 4] = (i & 0x00000000ff000000) >> 24;
	dataBuffer[bufferCounter + 5] = (i & 0x0000000000ff0000) >> 16;
	dataBuffer[bufferCounter + 6] = (i & 0x000000000000ff00) >> 8;
	dataBuffer[bufferCounter + 7] = (i & 0x00000000000000ff);
	bufferCounter += 8;
}

void NetworkBuffer::WriteFloat32(float f)
{
	WriteUnsignedInt32(BytePacker::PackFloat32(f));
}

void NetworkBuffer::WriteFloat64(double d)
{
	WriteUnsignedInt64(BytePacker::PackFloat64(d));
}

unsigned char NetworkBuffer::ReadUnsignedByte()
{
	unsigned char value = dataBuffer[readCounter];
	readCounter++;
	return value;
}

signed char NetworkBuffer::ReadSignedByte()
{
	signed char value = dataBuffer[readCounter];
	readCounter++;
	return value;
}

signed short int NetworkBuffer::ReadSignedInt16()
{
	signed short int value =
		(dataBuffer[readCounter++] << 8)
		| dataBuffer[readCounter++];

	value = ntohs(value);
	return value;
}

unsigned short int NetworkBuffer::ReadUnsignedInt16()
{
	unsigned short int value =
		(dataBuffer[readCounter++] << 8)
		| dataBuffer[readCounter++];

	value = ntohs(value);
	return value;
}

signed int NetworkBuffer::ReadSignedInt32()
{
	signed int value =
		(dataBuffer[readCounter++] << 24)
		| (dataBuffer[readCounter++] << 16)
		| (dataBuffer[readCounter++] << 8)
		| dataBuffer[readCounter++];

	value = ntohl(value);
	return value;
}

unsigned int NetworkBuffer::ReadUnsignedInt32()
{
	unsigned int value =
		(dataBuffer[readCounter++] << 24)
		| (dataBuffer[readCounter++] << 16)
		| (dataBuffer[readCounter++] << 8)
		| dataBuffer[readCounter++];

	value = ntohl(value);
	return value;
}

signed long int NetworkBuffer::ReadSignedInt64()
{
	signed long int value =
		((unsigned long int)dataBuffer[readCounter++] << 56)
		| ((unsigned long int)dataBuffer[readCounter++] << 48)
		| ((unsigned long int)dataBuffer[readCounter++] << 40)
		| ((unsigned long int)dataBuffer[readCounter++] << 32)
		| ((unsigned long int)dataBuffer[readCounter++] << 24)
		| ((unsigned long int)dataBuffer[readCounter++] << 16)
		| ((unsigned long int)dataBuffer[readCounter++] << 8)
		| (unsigned long int)dataBuffer[readCounter++];

	value = static_cast<signed long int>(BytePacker::ntohll(value));
	return value;
}

unsigned long int NetworkBuffer::ReadUnsignedInt64()
{
	unsigned long int value =
		((unsigned long int)dataBuffer[readCounter++] << 56)
		| ((unsigned long int)dataBuffer[readCounter++] << 48)
		| ((unsigned long int)dataBuffer[readCounter++] << 40)
		| ((unsigned long int)dataBuffer[readCounter++] << 32)
		| ((unsigned long int)dataBuffer[readCounter++] << 24)
		| ((unsigned long int)dataBuffer[readCounter++] << 16)
		| ((unsigned long int)dataBuffer[readCounter++] << 8)
		| (unsigned long int)dataBuffer[readCounter++];

	value = BytePacker::ntohll(value);
	return value;
}

float NetworkBuffer::ReadFloat32()
{
	return BytePacker::UnpackFloat32(ReadUnsignedInt32());
}

double NetworkBuffer::ReadFloat64()
{
	return BytePacker::UnpackFloat64(ReadUnsignedInt64());
}

}