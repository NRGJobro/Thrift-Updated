#include "Category.h"
#include "../Manager.h"
#include "Module/Module.h"

Category::Category(Manager* m, std::string n) {

	this->mgr = m;
	this->name = n;
	
	this->mgr->categories.push_back(this);

};

auto Category::baseTick(void) -> void {

	for (auto mod : this->modules) {

		mod->baseTick();

	};
}