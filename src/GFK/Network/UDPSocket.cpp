#include <GFK/Network/UDPSocket.hpp>
#include <iostream>

namespace gfk
{

bool UDPSocket::socketsInitialized = false;

UDPSocket::UDPSocket() :
handle(0),
socketPort(0)
{

}

UDPSocket::~UDPSocket()
{
	Close();
}

bool UDPSocket::Open(unsigned short port)
{
	if (IsOpen())
	{
		Close();
	}

	// Create the socket
	handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (handle <= 0)
	{
		std::cerr << "Failed to create a UDP socket on port " << port << std::endl;
		Close();
		return false;
	}

	// Bind the socket to a port
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short)port);

	if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		std::cerr << "Failed to bind UDP socket with handle " << handle << " on port " << port << std::endl;
		Close();
		return false;
	}

	socketPort = port;

	std::cout << "Opened UDP socket on port " << socketPort << " with handle " << handle << std::endl;

	// Set socket to non-blocking mode
	#if defined(PLATFORM_WINDOWS)
		DWORD nonBlocking = 1;
		if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
		{
			std::cerr << "Could not set socket with handle " << handle << " to non-blocking IO" << std::endl;
			return false;
		}
	#else
		int nonBlocking = 1;
		if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
		{
			std::cerr << "Could not set socket with handle " << handle << " to non-blocking IO" << std::endl;
			return false;
		}
	#endif

	return true;
}

void UDPSocket::Close()
{
	if (IsOpen())
	{
		std::cout << "Closing socket with handle " << handle << " on port " << socketPort << std::endl;;

		#if defined(PLATFORM_WINDOWS)
			closesocket(handle);
		#else
			close(handle);
		#endif

		handle = 0;
		socketPort = 0;
	}
}

bool UDPSocket::IsOpen() const
{
	return handle != 0;
}

bool UDPSocket::Send(const IPAddress &destination, const void *data, int size)
{
	if (handle == 0 || size <= 0)
	{
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.GetAddress());
	address.sin_port = htons((unsigned short) destination.GetPort());

	int sent_bytes = sendto(handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

	return sent_bytes == size;
}

int UDPSocket::Receive(IPAddress &sender, void *data, int size)
{
	if (handle == 0 || size <= 0)
	{
		return 0;
	}	

	#if defined(PLATFORM_WINDOWS)
		typedef int socklen_t;
	#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int received_bytes = recvfrom(handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	if (received_bytes <= 0)
	{
		return 0;
	}

	unsigned int address = ntohl(from.sin_addr.s_addr);
	unsigned int port = ntohs(from.sin_port);

	sender = IPAddress(address, port);

	return received_bytes;
}

bool UDPSocket::InitializeSocketLayer()
{
	#if defined(PLATFORM_WINDOWS)
		WSADATA WsaData;
		return WSAStartup(MAKEWORD(2,2), &WsaData) == NO_ERROR;
	#else
		return true;
	#endif
}

void UDPSocket::ShutdownSocketLayer()
{
	#if defined(PLATFORM_WINDOWS)
		WSACleanup();
	#endif
}

}