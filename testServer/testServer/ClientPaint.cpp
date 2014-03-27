//#include "stdafx.h"
#include "ClientPaint.h" 

ClientPaint::ClientPaint(void)
{

	network = new ClientNetwork();

	// send init packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientPaint::sendActionPackets()
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.contents = 'A';
	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientPaint::sendPacket(Packet _packet) {
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	_packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

Packet ClientPaint::update()
{
	Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0)
	{
		//no data recieved
		return;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {

		case ACTION_EVENT:

			printf("client received action event packet from server: %c\n", packet.contents);

			sendActionPackets();
			return packet;

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	}
	
	//ready or not, we must return something!
	return packet;
}

