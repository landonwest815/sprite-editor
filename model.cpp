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
    currentFrame(nullptr),
    currentFrameIndex(0)
{
    //Temporarily hard-coded the size to be 16
    frameSize = 16;

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

void Model::addNewFrame() {
    Frame newFrame(frameSize);

    // The color to set all pixels to
    QColor backgroundColor(64, 64, 64);

    // Fill the new frame with the background color
    for (int x = 0; x < frameSize; ++x) {
        for (int y = 0; y < frameSize; ++y) {
            newFrame.SetColor(std::make_pair(x, y), backgroundColor);
        }
    }

    // Add the new frame to the list of frames
    frames.push_back(newFrame);
}

void Model::removeFrame(int index) {
    frames.erase(frames.begin() + index);
}

void Model::setCurrentFrame(int index) {
    currentFrame = &frames[index];
    currentFrameIndex = index;
}

Frame& Model::getCurrentFrame() {
    return *currentFrame;
}

int Model::getCurrentFrameIndex() {
    return currentFrameIndex;
}

int Model::getFrameSize() {
    return frameSize;
}

void Model::setFrameSize(int newSize) {
    frameSize = newSize;
}

vector<Frame>& Model::getAllFrames() {
    return frames;
}
