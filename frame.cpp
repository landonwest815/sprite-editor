/************************
 *Frame Class
 *Project: Sprite Editor
 *Assignment: A8 Sprite Editor Implementation
 *Team Geoff
 *Description: Represents a single frame of animation for a sprite. Uses a map with coordinates as the key and the color as the value to store the pixel art.
 * **********************/
#include "frame.h"
#include <utility>
using std::pair;

bool operator <(const std::pair<int,int> point1, const std::pair<int,int> point2) {
    if((point1.first < point2.first) || ((point1.first == point2.first) && (point1.second < point2.second))) {
        return true;
    }
    return false;
}

Frame::Frame(int size, QColor backgroundColor) {
    this->size = size;
    this->backgroundColor = backgroundColor;
}

QMap<std::pair<int,int>, QColor> Frame::getPixelMap() const{
    return PixelMap;
}

void Frame::setPixelMap(QMap<std::pair<int,int>, QColor> newMap) {
    PixelMap = newMap;
}

int Frame::getSize() const{
    return size;
}

void Frame::SetColor(std::pair<int,int> coord, QColor color) {
    PixelMap[coord] = color;
}

void Frame::SetTransparent(std::pair<int,int> coord) {
    PixelMap[coord] = backgroundColor;
}

void Frame::ClearCanvas() {
    PixelMap.clear();
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
