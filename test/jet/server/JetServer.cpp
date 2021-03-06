#include "JetServer.hpp"
#include "network/Packet.hpp"
#include "network/ClientType.hpp"
#include <GFK/System/Logger.hpp>
#include <bitset>

using namespace jetGame;

JetServer::JetServer() :
ConsoleGame(true, 60),
networkCounter(0),
networkSendsPerSecond(20),
updateCounter(0),
playerIdCounter(0),
netHelper(NetworkHelper::ConnectionType::Server)
{

}

JetServer::~JetServer()
{

}

void JetServer::Initialize()
{
	gfk::ConsoleGame::Initialize();

	netHelper.StartServer(55777);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, clientData, gameTime);
		}
	);
}

void JetServer::LoadContent()
{
	gfk::ConsoleGame::LoadContent();
}

void JetServer::UnloadContent()
{
	gfk::ConsoleGame::UnloadContent();
}

void JetServer::Update(const gfk::GameTime &gameTime)
{
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToPlayers(gameTime);
	updateCounter++;
}

void JetServer::UpdateNetwork(const gfk::GameTime &gameTime)
{
	netHelper.Receive(gameTime);
}

void JetServer::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
{
	if (protocol == Packet::NEW_DESKTOP_CLIENT_REQ)
	{
		clientData.id = playerIdCounter;
		clientData.clientType = ClientType::DESKTOP;
		Logger::Logf("New desktop user connected. ID is: %d\n", clientData.id);
		playerIdCounter++;
		clientData.jet.Reset();

		// Inform all users of the new client
		netHelper.WritePacket(NewDesktopClientPacketRes(clientData.id));

		// Inform the new users of the existing clients
		netHelper.ForEachClient([this, &clientData](const ClientData &data)
			{
				if (data.id == clientData.id)
				{
					return;
				}

				if (data.clientType == ClientType::DESKTOP)
				{
					clientData.outbox.WritePacket(NewDesktopClientPacketRes(data.id));
				}
				else if (data.clientType == ClientType::GFK_ANDROID)
				{
					clientData.outbox.WritePacket(NewAndroidClientPacketRes(data.id));
				}

			}
		);

		clientData.outbox.WritePacket(ClientIdPacketRes(clientData.id));
	}
	else if (protocol == Packet::NEW_ANDROID_CLIENT_REQ)
	{
		clientData.id = playerIdCounter;
		clientData.clientType = ClientType::GFK_ANDROID;
		Logger::Logf("New Android user connected. ID is: %d\n", clientData.id);
		playerIdCounter++;
		clientData.jet.Reset();

		// Inform all users of the new client
		netHelper.WritePacket(NewAndroidClientPacketRes(clientData.id));

		// Inform the new users of the existing clients
		netHelper.ForEachClient([this, &clientData](const ClientData &data)
			{
				if (data.id == clientData.id)
				{
					return;
				}

				if (data.clientType == ClientType::DESKTOP)
				{
					clientData.outbox.WritePacket(NewDesktopClientPacketRes(data.id));
				}
				else if (data.clientType == ClientType::GFK_ANDROID)
				{
					clientData.outbox.WritePacket(NewAndroidClientPacketRes(data.id));
				}

			}
		);
	}
	else if (protocol == Packet::JET_INPUT_REQ)
	{
		float throttleAmt = netBuffer.ReadFloat32();
		float rollInput = netBuffer.ReadFloat32();
		float pitchInput = netBuffer.ReadFloat32();
		float yawInput = netBuffer.ReadFloat32();
		float thrusterEnabled = netBuffer.ReadUnsignedByte();
		unsigned int updateCount = netBuffer.ReadUnsignedInt32();

		clientData.jet.Update(throttleAmt, rollInput, pitchInput, yawInput, thrusterEnabled == 1, gameTime);
	}
	else if (protocol == Packet::DISCONNECT_REQ)
	{
		Logger::Logf("User %hu wants to disconnect\n", clientData.id);
		netHelper.WritePacket(DisconnectPacketRes(clientData.id));
	}
}

void JetServer::UpdateGame(const gfk::GameTime &gameTime)
{

}

void JetServer::SendStateToPlayers(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		netHelper.ForEachClient([this](const ClientData &clientData)
			{
				// Write jet data for all clients
				netHelper.WritePacket(JetInputPacketRes(clientData.id, clientData.jet.GetPosition(), clientData.jet.GetRotation()));
			}
		);

		netHelper.Send();

		networkCounter = 1;
	}
	else
	{
		networkCounter++;
	}
}

int main()
{
	JetServer server;
	server.Run();

	return 0;
}
