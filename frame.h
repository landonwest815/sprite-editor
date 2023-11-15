#ifndef FRAME_H
#define FRAME_H
#include <QMap>
#include <QColor>
#include <utility>

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * This project helps to demonstrate some C++ conventions in regards
 * to the topic of a Frame class which has been splitted into a header
 * file. It assists in declarations of the Frame object, functions, etc.
 */

class Frame
{
private:
    ///@brief Dictionary of all of the colored pixels in the Frame object
    QMap<std::pair<int,int>, QColor> PixelMap;
    ///@brief The size of the frame
    int size;
    /// \brief backgroundColor - color of the background
    QColor backgroundColor;

public:
    ///@brief Default constructor for the frame, in which the size can be set
    Frame(int size, QColor backgroundColor);

    ///@brief Returns the pixel map
    ///@return - The current pixel map
    QMap<std::pair<int,int>, QColor> getPixelMap() const;

    ///@brief Set a new pixel map for the frame
    ///@param - The new pixel map to set
    void setPixelMap(QMap<std::pair<int,int>, QColor>);

    ///@brief Getter for frame size
    ///@return - The size of the frame
    int getSize() const;

    ///@brief Set the particular color of a pixel on the pixel map
    void SetColor(std::pair<int,int> coord, QColor color);

//    ///@brief Clear the particular color of a pixel on the pixel map
//    void SetTransparent(std::pair<int,int> coord);

//    ///@brief Clear the entire canvas
//    void ClearCanvas();

    /// \brief toggleBackgroundColor - changes the background color when different modes selected
    /// (like Dark mode or Light mode)
    /// \param newColor - The color that will be set onto the background of the frame
    void toggleBackgroundColor(QColor newColor);
};

#endif // FRAME_H
