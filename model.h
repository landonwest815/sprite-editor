#ifndef MODEL_H
#define MODEL_H
#include <QColor>
#include <string>
#include <vector>
#include "frame.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * This project helps to demonstrate some C++ conventions in regards
 * to the topic of a Model class which has been splitted into a header
 * file. It assists in declarations of the Model object, functions, etc.
 */

class Model {
private:
    QColor selectedColor;
    std::vector<Frame> frames;
    Frame* currentFrame;
    int frameSize;
    int currentFrameIndex;
    QColor backgroundColor;

public:
    ///@brief Blank constructor for the Model class. Sets the selected tool to the brush and selected color to black.
    Model();

    ///@brief setter for the currently selected color
    ///@param color - color to be selected
    void setSelectedColor(QColor color);

    ///@brief getter for the currrently selected color
    ///@return - The currently selected color
    QColor getSelectedColor();

    QColor getBackgroundColor();

    void setBackgroundColor(QColor color);

    /// @brief addNewFrame Adds a new frame to the sprite editor
    void addNewFrame();

    void duplicateNewFrame(Frame&);

    /// @brief removeFrame Removes frame from the sprite editor
    /// @param index index of the frame to remove.
    void removeFrame(int index);

    ///@brief getter for the currrently selected frame
    ///@return - The currently selected frame
    Frame& getCurrentFrame();

    int getCurrentFrameIndex();

    ///@brief getter for size of the frames in the vector
    ///@return - The frame size
    int getFrameSize();

    ///@brief setter for size of the frames in the vector
    ///@param - The new frame size
    void setFrameSize(int newSize);

    ///@brief getter for the entire vector of frames
    ///@return - The entire vector of frames
    std::vector<Frame>& getAllFrames();

    ///@brief s]etter for the entire vector of frames
    ///@return - The entire vector of frames
    void setAllFrames(std::vector<Frame>);

    /// \brief setCurrentFrame Sets the current frame to the one the user selects
    /// \param index the index of the frame in the array
    void setCurrentFrame(int index);

    /// \brief getNumberOfFrames gets the size of the frames vector
    /// \return returns the size of the frames vector
    int getNumberOfFrames();

    void clearModel();
};

#endif // MODEL_H

