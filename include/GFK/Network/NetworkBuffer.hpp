#pragma once

#include <GFK/Network/UDPSocket.hpp>
#include <vector>

namespace gfk
{

class NetworkBuffer
{
public:
	NetworkBuffer(unsigned int capacity);
	~NetworkBuffer();

	unsigned int GetBufferCapacity();
	unsigned int GetBufferCount();
	unsigned char* GetDataBuffer();

	void WriteSignedByte(signed char c);
	void WriteUnsignedByte(unsigned char c);
	void WriteSignedInt16(signed short int i);
	void WriteUnsignedInt16(unsigned short int i);
	void WriteSignedInt32(signed int i);
	void WriteUnsignedInt32(unsigned int i);
	void WriteSignedInt64(signed long long int i);
	void WriteUnsignedInt64(unsigned long long int i);
	void WriteFloat32(float f);
	void WriteFloat64(double d);
	void WriteHeader(NetworkBuffer &headerBuffer);
	void WriteHeaderNoCountIncrement(NetworkBuffer &headerBuffer);

	unsigned char ReadUnsignedByte();
	signed char ReadSignedByte();
	signed short int ReadSignedInt16();
	unsigned short int ReadUnsignedInt16();
	signed int ReadSignedInt32();
	unsigned int ReadUnsignedInt32();
	signed long long int ReadSignedInt64();
	unsigned long long int ReadUnsignedInt64();
	float ReadFloat32();
	double ReadFloat64();

	void PopulateData(unsigned char *data, size_t length);

	void Reset();
protected:
private:
	unsigned int bufferCapacity;
	int bufferCounter;
	int readCounter;
	std::vector<unsigned char> dataBuffer;
};

}
