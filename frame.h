#ifndef FRAME_H
#define FRAME_H
#include <QMap>
#include <QColor>

class Frame
{
private:
    QMap<std::pair<int,int>, QColor> PixelMap;
    int size;
public:
    Frame(int size);
    void SetColor(std::pair<int,int> coord, QColor color);
    void SetTransparent(std::pair<int,int> coord);
    void ClearCanvas();
};

#endif // FRAME_H
