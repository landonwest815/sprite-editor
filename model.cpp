#include "model.h"
#include "Tool.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * Stores internal data for the sprite. This includes a list of frames for the
 * animation and the currently selected color.
 */

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

QColor Model::getBackgroundColor() {
    return backgroundColor;
}

void Model::setBackgroundColor(QColor color) {
    backgroundColor = color;
}

std::vector<Tool> Model::getTools() {
    return toolBar;
}

void Model::addNewFrame() {
    Frame newFrame(frameSize, backgroundColor);

    // Fill the new frame with the background color
    for (int x = 0; x < frameSize; ++x) {
        for (int y = 0; y < frameSize; ++y) {
            newFrame.SetColor(std::make_pair(x, y), backgroundColor);
        }
    }

    // Add the new frame to the list of frames
    frames.push_back(newFrame);
}

void Model::duplicateNewFrame(Frame& frame) {
    Frame newFrame = frame;
    frames.push_back(newFrame);
}

void Model::removeFrame(int index) {
    frames.erase(frames.begin() + index);
    currentFrameIndex = std::max(0, currentFrameIndex - 1);
    if (!frames.empty()) {
        currentFrame = &frames[currentFrameIndex];
    } else {
        addNewFrame();
        setCurrentFrame(0);
    }
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

std::vector<Frame>& Model::getAllFrames() {
    return frames;
}

void Model::setAllFrames(std::vector<Frame> newFrames) {
    frames = newFrames;
}

int Model::getNumberOfFrames(){
    return (int)frames.size();
}
