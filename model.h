#ifndef MODEL_H
#define MODEL_H

#include "Tool.h"
#include <QColor>
#include <string>

class Model
{
private:
    Tool draw;
    Tool erase;
    Tool mirror;
    QColor selectedColor;

public:
    ///@brief Blank constructor for the Model class. Sets the selected tool to the brush and selected color to black.
    Model();
    ///@brief Constructor for the model class with parameters for the selected tool and color.
    /// @param selectedTool - Tool to be selected once the class is initialized.
    /// @param selectedColor - Color to be selected once the class is initialized.
    Model(Tool selectedTool, QColor selectedColor);

    ///@brief setter for the currently selected tool
    ///@param toolName - name of the tool to be selected
    void setSelectedTool(std::string toolName);
    ///@brief getter for the currrently selected tool
    ///@return - The currently selected tool
    Tool getSelectedTool();

    ///@brief setter for the currently selected color
    ///@param color - color to be selected
    void setSelectedColor(QColor color);
    ///@brief getter for the currrently selected color
    ///@return - The currently selected color
    Tool getSelectedColor();
};

#endif // MODEL_H
