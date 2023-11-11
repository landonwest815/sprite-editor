#ifndef FRAME_H
#define FRAME_H
#include <QMap>
#include <QColor>

class Frame
{
private:
    ///@brief Dictionary of all of the colored pixels in the Frame object
    QMap<std::pair<int,int>, QColor> PixelMap;
    ///@brief The size of the frame
    int size;

public:
    ///@brief Default constructor for the frame, in which the size can be set
    Frame(int size);

    ///@brief Returns the pixel map
    ///@return - The current pixel map
    QMap<std::pair<int,int>, QColor> getPixelMap();

    ///@brief Set a new pixel map for the frame
    ///@param - The new pixel map to set
    void setPixelMap(QMap<std::pair<int,int>, QColor>);

    ///@brief Getter for frame size
    ///@return - The size of the frame
    int getSize();

    ///@brief Set the particular color of a pixel on the pixel map
    void SetColor(std::pair<int,int> coord, QColor color);

    ///@brief Clear the particular color of a pixel on the pixel map
    void SetTransparent(std::pair<int,int> coord);

    ///@brief Clear the entire canvas
    void ClearCanvas();
};

#endif // FRAME_H
