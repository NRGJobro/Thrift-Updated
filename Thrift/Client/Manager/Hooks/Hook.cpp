#include "Hook.h"
#include "../Manager.h"

Hook::Hook(Manager* m) {

	this->mgr = m;
	this->mgr->hooks.push_back(this);

};