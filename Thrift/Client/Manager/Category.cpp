#include "Category.h"
#include "Manager.h"
#include "Module.h"

Category::Category(Manager* m, std::string n) {

    this->mgr = m;
    this->name = n;
    this->index = -1; // Initialize index with a default value

    this->mgr->categories.push_back(this);

};

auto Category::baseTick(void) -> void {

    for (auto mod : this->modules) {
        mod->baseTick();
    }
}