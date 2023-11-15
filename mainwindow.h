#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtTextToSpeech/QTextToSpeech>
#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDialog>
#include <QButtonGroup>
#include <QScrollBar>
#include <QMessageBox>
#include <QComboBox>
#include "filemanager.h"
#include "model.h" // Ensure this includes the definition of the Model class

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * This project helps to demonstrate some C++ conventions in regards
 * to the topic of a MainWindow class which has been splitted into a header
 * file. It assists in declarations of the MainWindow object, functions, etc.
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Represents the main window of the sprite editor. The MainWindow class provides
 * the user interface for the sprite editor application. It includes various tools, canvas,
 * and options for creating and editing frames.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Constructor for the MainWindow
    explicit MainWindow(QWidget *parent = nullptr);

    /// @brief Destructor for MainWindow
    ~MainWindow();

private slots:
    /// @brief Handles the "Add Frame" button click.
    void addFrameClicked();

    /// @brief Handles the "Duplicate Frame" button click.
    void duplicateFrameClicked();

    /// @brief Handles the selection of a frame.
    void handleFrameClicked();

    /// @brief Sets the RGB values based on the color picker.
    void setRGB();

    /// @brief Handles the click event of tool buttons.
    void onToolButtonClicked(int id);

    /// @brief Handles the selection of FPS in the combo box.
    void onSelectFPS(int FPS);

    /// @brief Handles the click event of the "Animate" button.
    void onAnimateButtonClicked();

    /// @brief Updates the preview window during animation.
    void updatePreviewWindow();

    /// @brief Handles the click event of the "Stop Animation" button.
    void onStopAnimationClicked();

    /// @brief Handles the click event of the color button.
    void onColorButtonClicked();

private:
    /// The user interface object.
    Ui::MainWindow *ui;

    /// The image object for the canvas.
    QImage image;

    /// The pixmap object for drawing.
    QPixmap pix;

    /// The data model for the sprite editor.
    Model model;

    /// The file manager object.
    FileManager* file;

    /// Counter for frames.
    int frameCounter;

    /// Button group for tool selection.
    QButtonGroup* toolButtonGroup;

    /// Map to store frame thumbnails.
    QMap<int, QPushButton*> frameThumbnails;

    /// Timer for animation.
    QTimer timer;

    /// Frames per second for animation.
    int FPS;

    /// Flag indicating whether preview is in animation mode.
    bool animatingPreview;

    /// Flag indicating whether dark mode is enabled.
    bool darkMode;

    /// Flag indicating whether speech mode is enabled.
    bool speech;

    /// Text-to-speech object.
    QTextToSpeech say;

    /// Combo box for selecting canvas size.
    QComboBox *sizeComboBox;

    /// Dialog for selecting canvas size.
    QDialog *frameSizeDialog;

    /// @brief Overridden method to handle mouse press events.
    /// @param Event The mouse press event.
    void mousePressEvent(QMouseEvent *event) override;

    /// @brief Overridden method to handle mouse move events.
    /// @param Event The mouse move event.
    void mouseMoveEvent(QMouseEvent *event) override;

    /// @brief Asks the user to select the canvas size.
    void askForFrameSize();

    /// @brief Initializes main components of the UI for the user.
    void initializeUI();

    /// @brief Connects UI elements to different slots.
    void setupConnections();

    /// @brief Used to update all the pixel maps of the current frame.
    void updateAllPixmaps();

    /// @brief Clears focus on widgets.
    void clearFocusOnWidgets();

    /// @brief Updates the image and canvas based on the given position.
    /// @param pos The position.
    void updateImageAndCanvas(const QPoint &pos);

    /// @brief Checks if the mouse is on the canvas to draw to.
    /// @param pos The position of the mouse.
    /// @return Returns true if it is a valid position, false otherwise.
    bool isValidCanvasPos(const QPoint& pos) const;

    /// @brief Returns a point on the canvas to use for coloring.
    /// @param pos The position of the mouse.
    /// @return Returns a point on the canvas.
    QPoint mapToCanvasPos(const QPoint& pos) const;

    /// @brief Sets a pixmap to the scale of the label.
    /// @param label The label that will contain the pixmap.
    /// @param pixmap The pixmap that will be scaled to the label.
    void setScaledCanvas(QLabel* label, const QPixmap &pixmap);

    /// @brief Sets a pixmap to the scale of the icon on the button.
    /// @param button The button that will use the scaled pixmap.
    /// @param pixmap The pixmap that will be scaled to the button icon size.
    void setScaledButton(QPushButton* button, const QPixmap &pixmap);

    /// @brief Updates the UI when a new frame is added.
    /// @param frameIndex The index of the new frame.
    void updateUIForNewFrame(int frameIndex);

    /// @brief Creates a QImage using a frame.
    /// @param frame The frame from the model class.
    /// @return Returns a QImage of the frame.
    QImage createImageFromFrame(const Frame &frame);

    /// @brief Updates the UI for the frame that was selected by the user on the UI.
    /// @param frameIndex The index of the selected frame.
    void updateUIForSelectedFrame(int frameIndex);

    /// @brief Deletes a frame from the Sprite Editor.
    /// @param frameIndex The index of the frame to be deleted.
    void deleteFrame(int frameIndex);

    /// @brief Updates the frame indices to stay up to date with underlying changes.
    void updateFrameIndices();

    /// @brief Makes a QPixmap based on the given frame.
    /// @param frame The frame to be converted into a QPixmap.
    /// @return Returns a QPixmap object.
    QPixmap getPixMap(Frame frame);

    /// @brief Shows the tutorial popup menu when called.
    void showTutorialPopup();

    /// @brief Sets the UI to dark mode or light mode depending on the context of UI.
    void darkOrLightModeClicked();

    /// @brief Sets the text to large when the user clicks on the button.
    /// @param size The size of the text.
    void largeTextClicked(int size);

    /// @brief Enables or disables speech mode.
    /// @param mode The speech mode (1 for enable, 0 for disable).
    void speechModeClicked(int mode);

    /// @brief Saves the file to a .ssp file and allows you to choose the location of save.
    void saveFile();

    /// @brief Loads a .ssp file into the current project.
    void loadFile();

    /// @brief When the speech assistant is activated, the assistant says the object's name.
    void sayObjectName();

    /// @brief Loops through the frames and updates their thumbnails.
    void updateAllThumbnails();

    /// @brief Calculates the vertical mirror pixel of where the user is drawing.
    /// @param pixX The x-coordinate of the pixel.
    /// @param pixY The y-coordinate of the pixel.
    /// @param selectedColor The selected color that the user has active.
    void mirrorPixel(int pixX, int pixY, QColor selectedColor);

    /// @brief Shows an error message.
    /// @param message The error message to show.
    void showError(QString message);

    /// @brief Updates thumbnails from the model.
    void updateThumbnailsFromModel();
};

#endif // MAINWINDOW_H
