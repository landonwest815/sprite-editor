/************************
 *Model Class
 *Project: Sprite Editor
 *Assignment: A8 Sprite Editor Implementation
 *Team Geoff
 *Description: Stores internal data for the sprite. This includes a list of frames for the animation and the currently selected color.
 * **********************/
#include "model.h"
#include "Tool.h"
#include <vector>

Model::Model() :
    toolBar(),
    selectedColor(255,255,255)
{
    toolBar.push_back(*new Tool("draw",false));
    toolBar.push_back(*new Tool("erase",false));
    toolBar.push_back(*new Tool("mirror",true));
}

QColor Model::getSelectedColor() {
    return selectedColor;
}

void Model::setSelectedColor(QColor color) {
    selectedColor = color;
}

std::vector<Tool> Model::getTools() {
    return toolBar;
}
