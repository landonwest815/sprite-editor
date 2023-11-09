#ifndef FRAME_H
#define FRAME_H
#include <QPoint>
#include <QMap>
#include <string>

class Frame
{
private:
    QMap<QPoint, std::string> PixelMap;
    int size;
public:
    Frame(int size);
    void SetColor(QPoint coord, std::string color);
    void SetTransparent(QPoint coord);
    void ClearCanvase();
};

#endif // FRAME_H
