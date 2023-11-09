#include "frame.h"
#include <utility>
using std::pair;

bool operator <(const QPoint point1, const QPoint point2){
    if((point1.x() < point2.x()) || ((point1.x() == point2.x()) && (point1.y() < point2.y()))){
        return true;
    }
    return false;
}
Frame::Frame(int size)
{
    this->size = size;
}
void Frame::SetColor(QPoint coord, QColor color)
{
    PixelMap[coord] = color;
}
void Frame::SetTransparent(QPoint coord){
    PixelMap[coord] = QColor::fromRgb(64, 64, 64);
}
void Frame::ClearCanvas(){
    PixelMap.clear();
}
