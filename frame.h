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

#ifndef FRAME_H
#define FRAME_H

#include <QMap>
#include <QColor>
#include <utility>

/**
 * @brief The Frame class represents a frame in the sprite editor.
 * It stores information about the colored pixels, size, and background color of the frame.
 */
class Frame {
private:
    /// @brief Dictionary of all colored pixels in the Frame object.
    QMap<std::pair<int, int>, QColor> PixelMap;

    /// @brief The size of the frame.
    int size;

    /// @brief The background color of the frame.
    QColor backgroundColor;

public:
    /// @brief Constructor for the Frame class.
    /// @param size The size of the frame.
    /// @param backgroundColor The background color of the frame.
    Frame(int size, QColor backgroundColor);

    /// @brief Getter for the pixel map of the frame.
    /// @return The current pixel map.
    QMap<std::pair<int, int>, QColor> getPixelMap() const;

    /// @brief Setter for the pixel map of the frame.
    /// @param pixelMap The new pixel map to set.
    void setPixelMap(QMap<std::pair<int, int>, QColor> pixelMap);

    /// @brief Getter for the size of the frame.
    /// @return The size of the frame.
    int getSize() const;

    /// @brief Set the color of a specific pixel on the pixel map.
    /// @param coord The coordinates of the pixel.
    /// @param color The color to set for the pixel.
    void setColor(std::pair<int, int> coord, QColor color);

    /// @brief Toggle the background color of the frame.
    /// @param newColor The color to set as the new background color.
    void toggleBackgroundColor(QColor newColor);
};

#endif // FRAME_H
