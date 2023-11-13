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
    Frame* currentFrame;
    int frameSize;

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

    ///@brief getter for the currrently selected frame
    ///@return - The currently selected frame
    Frame& getCurrentFrame();

    ///@brief getter for size of the frames in the vector
    ///@return - The frame size
    int getFrameSize();

    ///@brief setter for size of the frames in the vector
    ///@param - The new frame size
    void setFrameSize(int newSize);

    ///@brief getter for the entire vector of frames
    ///@return - The entire vector of frames
    vector<Frame>& getAllFrames();

    /// \brief setCurrentFrame Sets the current frame to the one the user selects
    /// \param index the index of the frame in the array
    void setCurrentFrame(int index);
};

#endif // MODEL_H

