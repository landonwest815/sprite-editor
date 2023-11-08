#include <string>
#include "Tool.h"

Tool::Tool(std::string newName, bool newTogglable) {
    name = newName;
    togglable = newTogglable;
}

std::string Tool::getName() {
    return name;
}

bool Tool::getSelected() {
    return selected;
}

void Tool::setSelected(bool newSelected) {
    selected = newSelected;
}

bool Tool::getTogglable() {
    return togglable;
}
