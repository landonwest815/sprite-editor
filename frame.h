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
