#include "Client.h"

Client::Client(std::string name) {

	this->setName(name);
	Utils::debugOutput("Client has been Initialized!");

	this->mgr = new Manager(this);

};

auto Client::setName(std::string n) -> void {

	this->name = n;
	Utils::setDebugPath(this->name);

};

auto Client::getName(void) -> std::string {

	return this->name;

};