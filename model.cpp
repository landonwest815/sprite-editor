/************************
 *Model Class
 *Project: Sprite Editor
 *Assignment: A8 Sprite Editor Implementation
 *Team Geoff
 *Description: Stores internal data for the sprite. This includes a list of frames for the animation and the currently selected color.
 * **********************/
#include "model.h"
#include "Tool.h"
#include <ostream>
#include <vector>

Model::Model() :
    toolBar(),
    selectedColor(255,255,255),
    frames(),
    currentFrame(16)
{
    //Temporarily hard-coded the size to be 16
    frameSize = 16;

    toolBar.push_back(*new Tool("draw",false));
    toolBar.push_back(*new Tool("erase",false));
    toolBar.push_back(*new Tool("mirror",true));

    frames.push_back(*new Frame(frameSize));
    currentFrame = frames[0];
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

void Model::addNewFrame() {
    frames.push_back(*new Frame(frameSize));
}

void Model::removeFrame(int index) {
    frames.erase(frames.begin() + index);
}

void Model::setCurrentFrame(int index) {
    currentFrame = frames[index];
}

Frame Model::getCurrentFrame() {
    return currentFrame;
}

vector<Frame> Model::getAllFrames() {
    return frames;
}
