#include "Tool.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * Stores information about the different tools used in the Srite Editor.
 */

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
