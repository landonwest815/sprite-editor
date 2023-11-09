#include "frame.h"
#include <utility>
using std::pair;

bool operator <(const std::pair<int,int> point1, const std::pair<int,int> point2){
    if((point1.first < point2.first) || ((point1.first == point2.first) && (point1.second < point2.second))){
        return true;
    }
    return false;
}
Frame::Frame(int size)
{
    this->size = size;
}
void Frame::SetColor(std::pair<int,int> coord, QColor color)
{
    PixelMap[coord] = color;
}
void Frame::SetTransparent(std::pair<int,int> coord){
    PixelMap[coord] = QColor::fromRgb(64, 64, 64);
}
void Frame::ClearCanvas(){
    PixelMap.clear();
}
