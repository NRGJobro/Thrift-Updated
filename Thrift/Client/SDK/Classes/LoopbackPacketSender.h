#pragma once

#include "Packet.h"

class LoopbackPacketSender {
public:
	virtual ~LoopbackPacketSender(); // constructor
	virtual void send(void* Packet);
	virtual void sendToServer(void* Packet);
	virtual void sendToClient(class UserEntityIdentifierComponent const*, void* Packet);
	virtual void sendToClient(class NetworkIdentifier const&, void* Packet, unsigned char);
	virtual void sendToClients(std::vector<class NetworkIdentifierWithSubId, std::allocator<class NetworkIdentifierWithSubId>> const&, void* Packet);
	virtual void sendBroadcast(void* Packet);
	virtual void sendBroadcast(class NetworkIdentifier const&, unsigned char, void* Packet);
	virtual void flush(class NetworkIdentifier const&);
};