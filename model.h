#ifndef MODEL_H
#define MODEL_H

#include "Tool.h"
#include <QColor>
#include <string>
#include <vector>
#include "frame.h"

using std::vector;
using std::string;

class Model
{
private:
    vector<Tool> toolBar;
    QColor selectedColor;
    vector<Frame> frames;

public:
    ///@brief Blank constructor for the Model class. Sets the selected tool to the brush and selected color to black.
    Model();

    ///@brief getter for all of the tools
    ///@return - Dynamic list (vector) of all of the tools
    vector<Tool> getTools();

    /// @brief getSelectedTool
    /// @return returns the tool the user wants to use
    Tool getSelectedTool();

    ///@brief setter for the currently selected color
    ///@param color - color to be selected
    void setSelectedColor(QColor color);

    ///@brief getter for the currrently selected color
    ///@return - The currently selected color
    QColor getSelectedColor();

    /// @brief addNewFrame Adds a new frame to the sprite editor
    void addNewFrame();

    /// @brief removeFrame Removes frame from the sprite editor
    /// @param index index of the frame to remove.
    void removeFrame(int index);

    // Canvas getCurrentFrame();

    /// \brief setCurrentFrame Sets the current frame to the one the user selects
    /// \param index the index of the frame in the array
    void setCurrentFrame(int index);
};

#endif // MODEL_H

#ifndef MODEL_H
#define MODEL_H
#include "frame.h"
#include "Tool.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Model
{
private:
    vector<Frame> frames;
    // Canvas currentFrame;
    // DropMenu dropMenu;
    Tool draw;
    Tool erase;
    Tool mirror;
    Tool selectedTool;
    string selectedColor;

public:
    Model();

    Model(Tool selectedTool, string selectedColor);

    void setSelectedTool(Tool selectedTool);

    Tool getSelectedTool();

    string getSelectedColor();

    void setSelectedColor(string color);

    void addNewFrame();

    void removeFrame(int index);

    // Canvas getCurrentFrame();

    void setCurrentFrame(int index);
};

#endif // MODEL_H

