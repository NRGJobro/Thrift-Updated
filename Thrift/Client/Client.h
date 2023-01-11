#pragma once

#include "Manager/Manager.h"

class Client {
public:
	std::string name;
	Manager* mgr;
public:
	Client(std::string);
public:
	auto setName(std::string)->void;
	auto getName(void)->std::string;
};