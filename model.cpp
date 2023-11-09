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
