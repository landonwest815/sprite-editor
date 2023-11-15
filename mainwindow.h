#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDialog>
#include "filemanager.h"
#include <QtTextToSpeech/QTextToSpeech>
#include "model.h" // Ensure this includes the definition of the Model class

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void addFrameClicked();
    void duplicateFrameClicked();
    void handleFrameClicked();
    void setRGB();
    void onToolButtonClicked(int id);
    void onSelectFPS(int FPS);
    void onAnimateButtonClicked();
    void updatePreviewWindow();
    void onStopAnimationClicked();
    void onColorButtonClicked();

private:
    Ui::MainWindow *ui;
    QImage image;
    QPixmap pix;
    Model model;
    FileManager file;
    int frameCounter;
    QButtonGroup* toolButtonGroup;
    QMap<int, QPushButton*> frameThumbnails;
    QTimer timer;
    int FPS;
    bool animatingPreview;
    bool darkMode;
    bool speech;
    QTextToSpeech say;

    /// \brief initializeUI Initializes main components of the UI for the User
    void initializeUI();
    /// \brief setupConnections- connects UI elements to different slots
    void setupConnections();
    /// \brief updateAllPixmaps Used to update all the pixel maps of the current frame
    void updateAllPixmaps();
    /// \brief clearFocusOnWidgets
    void clearFocusOnWidgets();
    /// \brief updateImageAndCanvas
    /// \param pos
    void updateImageAndCanvas(const QPoint &pos);
    /// \brief isValidCanvasPos Checks if mouse is on the canvas to draw to
    /// \param pos The position of the mouse of the user
    /// \return Returns true of false to whether it is a valid position.
    bool isValidCanvasPos(const QPoint& pos) const;
    /// \brief mapToCanvasPos returns a point on the canvas to use to color on the canvas
    /// \param pos the position of the mouse.
    /// \return Returns a Point that is on the Canvas
    QPoint mapToCanvasPos(const QPoint& pos) const;
    /// \brief setScaledCanvas Sets a pixmap to the scale of the label
    /// \param label The label that will contain the pixmap
    /// \param pixmap The pixmap that will be scaled to the label
    void setScaledCanvas(QLabel* label, const QPixmap &pixmap);
    /// \brief setScaledButton Sets a pixmap to the scale of the icon on the button
    /// \param button The button that will use the scaled pixmap
    /// \param pixmap The pixmap that will be scaled to the button icon size
    void setScaledButton(QPushButton* button, const QPixmap &pixmap);
    /// \brief updateUIForNewFrame Updates the UI when a new Frame is added
    /// \param frameIndex The index of the new frame that was added to the model frames array
    void updateUIForNewFrame(int frameIndex);
    /// \brief createImageFromFrame Creats a qImage using a frame.
    /// \param frame The frame comes from the model class
    /// \return Returns a QImage of the frame pased into the parameter
    QImage createImageFromFrame(const Frame &frame);
    /// \brief updateUIForSelectedFrame Updates the UI for the frame that was selected by the user on the UI
    /// \param frameIndex The index of the frame based on the model frames vector
    void updateUIForSelectedFrame(int frameIndex);
    /// \brief deleteFrame Deletes a frame from the Sprite Editor
    /// \param frameIndex The index of the frame to be deleted
    void deleteFrame(int frameIndex);
    /// \brief updateFrameIndices updates the frame indices so that it stays up to date with the underying
    /// things that are going on.
    void updateFrameIndices();
    /// \brief getPixMap Makes a QPixmap based on the frame given
    /// \param frame The frame that will be converted into a QPixmap
    /// \return returns a QPixmap object that can be used for different areas of the code
    QPixmap getPixMap(Frame frame);
    /// \brief showTutorialPopup Shows the tutorial popup menu when called
    void showTutorialPopup();
    /// \brief darkOrLightModeClicked Sets the UI to dark mode or light mode depending on context of UI
    void darkOrLightModeClicked();
    /// \brief largeTextClicked Sets the text to large when user clicks on the button
    void largeTextClicked(int);
    /// \brief speechModeClicked Enambls speech mode or disabls it
    void speechModeClicked(int);
    /// \brief saveFile Saves the file to a .ssp file and allows you to choose location of save
    void saveFile();
    /// \brief loadFile Loads a .ssp file into the current project
    void loadFile();
    /// \brief sayObjectName When speech assistant activated, assistant says the objects name
    void sayObjectName();
    /// \brief updateAllThumbnails Loops through the frames and updates their thumbnails.
    void updateAllThumbnails();
    /// \brief mirrorPixel Calculates the vertical mirror pixel of where the user is drawing
    /// \param pixX The x coord of the pixel
    /// \param pixY The y coord of the pixel
    /// \param selectedColor The selected Color that the user has active
    void mirrorPixel(int pixX, int pixY, QColor selectedColor);
};

#endif // MAINWINDOW_H
