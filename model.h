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

#ifndef MODEL_H
#define MODEL_H

#include <QColor>
#include <string>
#include <vector>
#include "frame.h"

/**
 * @brief The Model class represents the core data model of the sprite editor.
 * It manages information regarding all of the frames as well as the currently selected color,
 * background color, and various properties related to the editing canvas.
 */
class Model {
private:
    /// Currently selected color for drawing tools
    QColor selectedColor;

    /// Vector containing all frames in the sprite editor
    std::vector<Frame> frames;

    /// Pointer to the currently selected frame
    Frame* currentFrame;

    /// Size of the frames in the vector
    int frameSize;

    /// Index of the currently selected frame in the frames vector
    int currentFrameIndex;

    /// Currently selected color for the background
    QColor backgroundColor;

public:
    /// @brief Blank constructor for the Model class. Sets the selected tool to the brush and selected color to black.
    Model();

    /// @brief Setter for the currently selected color
    /// @param Color - color to be selected
    void setSelectedColor(QColor color);

    /// @brief Getter for the currrently selected color
    /// @return The currently selected color
    QColor getSelectedColor();

    /// @brief Getter for the current background color
    /// @return Currently selected color for the background
    QColor getBackgroundColor();

    /// @brief setter for the background colors
    void setBackgroundColor(QColor color);

    /// @brief AddNewFrame Adds a new frame to the sprite editor
    void addNewFrame();

    /// @brief Makes a copy of the frame carrying over its entire pixmap
    void duplicateNewFrame(Frame&);

    /// @brief RemoveFrame Removes frame from the sprite editor
    /// @param Index index of the frame to remove.
    void removeFrame(int index);

    /// @brief getter for the currrently selected frame
    /// @return the currently selected frame
    Frame& getCurrentFrame();

    /// @brief getter for the index of the current frame
    /// @return int index of frame
    int getCurrentFrameIndex();

    /// @brief Getter for size of the frames in the vector
    /// @return The frame size
    int getFrameSize();

    /// @brief Setter for size of the frames in the vector
    /// @param The new frame size
    void setFrameSize(int newSize);

    /// @brief Getter for the entire vector of frames
    /// @return The entire vector of frames
    std::vector<Frame>& getAllFrames();

    /// @brief Setter for the entire vector of frames
    /// @return The entire vector of frames
    void setAllFrames(std::vector<Frame>);

    /// @brief SetCurrentFrame Sets the current frame to the one the user selects
    /// @param Index the index of the frame in the array
    void setCurrentFrame(int index);

    /// @brief GetNumberOfFrames gets the size of the frames vector
    /// @return Returns the size of the frames vector
    int getNumberOfFrames();

    /// @brief Clears everything from model
    void clearModel();
};

#endif // MODEL_H

