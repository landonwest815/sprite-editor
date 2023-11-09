#ifndef MODEL_H
#define MODEL_H

#include "Tool.h"
#include <QColor>
#include <string>
#include <vector>

class Model
{
private:
    std::vector<Tool> toolBar;
    QColor selectedColor;

public:
    ///@brief Blank constructor for the Model class. Sets the selected tool to the brush and selected color to black.
    Model();

    ///@brief getter for all of the tools
    ///@return - Dynamic list (vector) of all of the tools
    std::vector<Tool> getTools();

    ///@brief setter for the currently selected color
    ///@param color - color to be selected
    void setSelectedColor(QColor color);
    ///@brief getter for the currrently selected color
    ///@return - The currently selected color
    QColor getSelectedColor();
};

#endif // MODEL_H
