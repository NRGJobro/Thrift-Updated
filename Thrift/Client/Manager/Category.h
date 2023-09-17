#pragma once

#include <vector>
#include <string>

class Manager;
class Module;

class Category {
public:
    Manager* mgr;
    std::string name;
    std::vector<Module*> modules;
    int index; // Add this member variable
public:
    Category(Manager*, std::string);
public:
    auto baseTick(void) -> void;
};