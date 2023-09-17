#pragma once

#include "../Utils/Utils.h"
#include "Category.h"

class Client;
class Hook;

class Manager {
public:
	Client* client;
	bool isRunning = false;
public:
	std::vector<Hook*> hooks;
	std::vector<Category*> categories;
public:
	Manager(Client*);
public:
	auto initHooks(void)->StatusData;
	auto initCategories(void)->void;
public:
	auto uninjectDLL(void) -> void;
};