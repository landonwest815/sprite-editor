#include "frame.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * Represents a single frame of animation for a sprite. Uses a map with coordinates
 * as the key and the color as the value to store the pixel art.
 */

Frame::Frame(int size, QColor backgroundColor) {
    this->size = size;
    this->backgroundColor = backgroundColor;
}

QMap<std::pair<int,int>, QColor> Frame::getPixelMap() const {
    return PixelMap;
}

void Frame::setPixelMap(QMap<std::pair<int,int>, QColor> newMap) {
    PixelMap = newMap;
}

int Frame::getSize() const {
    return size;
}

void Frame::setColor(std::pair<int,int> coord, QColor color) {
    PixelMap[coord] = color;
}

void Frame::toggleBackgroundColor(QColor newColor) {
    QMap<std::pair<int, int>, QColor>::iterator i;
    for (i = PixelMap.begin(); i != PixelMap.end(); ++i) {
        if (i.value() == backgroundColor) {
            i.value() = newColor; // Replace the old color with the new color
        }
    }
    backgroundColor = newColor;
}
