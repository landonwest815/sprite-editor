#ifndef FRAME_H
#define FRAME_H
#include <QPoint>
#include <QMap>
#include <QColor>

class Frame
{
private:
    QMap<QPoint, QColor> PixelMap;
    int size;
public:
    Frame(int size);
    void SetColor(QPoint coord, QColor color);
    void SetTransparent(QPoint coord);
    void ClearCanvas();
};

#endif // FRAME_H
