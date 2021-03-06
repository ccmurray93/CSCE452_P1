// may need #include "stdafx.h" in visual studio
//#include "stdafx.h"
#include "ServerPaint.h"
#include "ClientPaint.h"
// used for multi-threading
#include <process.h>

void serverLoop(void *);
void clientLoop(void);

ServerPaint * server;
ClientPaint * client;

int main()
{

	// initialize the server
	server = new ServerPaint();

	// create thread with arbitrary argument for the run function
	_beginthread(serverLoop, 0, (void*)12);

	// initialize the client 
	client = new ClientPaint();

	clientLoop();

	for (;;);
}

void serverLoop(void * arg)
{
	Packet pak;
	pak.packet_type = ACTION_EVENT;
	pak.contents = 'X';

	int i = 0;
	while (true)
	{
		if (i == 20000){
			server->close();
			client->close();
			break;
		}
		server->update(pak);
		++i;
	}
}

void clientLoop()
{
	Packet pak;
	pak.packet_type = ACTION_EVENT;
	pak.contents = 'Y';

	int i = 0;
	while (true)
	{
		if (i == 20000){
			client->close();
			server->close();
			break;
		}
		//do game stuff
		client->update(pak);
		++i;
	}
}

