#ifndef TOOL_H
#define TOOL_H
#include <string>

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * This project helps to demonstrate some C++ conventions in regards
 * to the topic of a Tool class which has been splitted into a header
 * file. It assists in declarations of the Tool object, functions, etc.
 */

class Tool {
private:
    //The name of the tool
    std::string name;
    //Stores whether the tool is selected or not
    bool selected;
    //If true, the tool can be selected with other tools, if false this tool cannot be selected with other tools
    bool togglable;

public:
    ///@brief Constructor for the Tool class, which takes in a name and whether the tool is togglable/// @param name - The name of the tool
    /// @param togglable - If the tool can be selected with other tools or not
    Tool(std::string name, bool togglable);

    ///@brief Sets whether the tool is selected or not
    /// @param selected - The selection status to set the tool to
    void setSelected(bool selected);

    ///@brief Gets the tool's selection status
    /// @return - The tool's selection status
    bool getSelected();

    ///@brief Gets the tool's name
    /// @return - The tool's name
    std::string getName();

    ///@brief Gets whether the tool is togglable or not
    /// @return - The tool's togglability
    bool getTogglable();
};

#endif // TOOL_H
