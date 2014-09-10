#include "network/Packet.hpp"

namespace jetGame
{

// Base Packet Class
Packet::Packet(unsigned char protocol) :
protocol(protocol)
{

}

Packet::~Packet()
{

}

void Packet::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	buffer.WriteUnsignedByte(protocol);
}

unsigned char Packet::GetPacketType()
{
	return protocol;
}


// NewDesktopClientAckPacket
NewDesktopClientAckPacket::NewDesktopClientAckPacket(unsigned char numPlayers) :
Packet(Packets::NEW_DESKTOP_CLIENT_ACK),
numPlayers(numPlayers)
{

}

void NewDesktopClientAckPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(numPlayers);
}


// NewAndroidClientAckPacket
NewAndroidClientAckPacket::NewAndroidClientAckPacket(unsigned char numPlayers) :
Packet(Packets::NEW_ANDROID_CLIENT_ACK),
numPlayers(numPlayers)
{

}

void NewAndroidClientAckPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
    Packet::WriteToBuffer(buffer);
    buffer.WriteUnsignedByte(numPlayers);
}


// MovementPacket
MovementPacket::MovementPacket(float x, float y, float z) :
Packet(Packets::MOVEMENT),
x(x), y(y), z(z)
{

}

void MovementPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteFloat32(x);
	buffer.WriteFloat32(y);
	buffer.WriteFloat32(z);
}

}
