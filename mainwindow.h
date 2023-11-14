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

    void initializeUI();
    void setupConnections();
    void updateAllPixmaps();
    void clearFocusOnWidgets();
    void updateImageAndCanvas(const QPoint &pos);
    bool isValidCanvasPos(const QPoint& pos) const;
    QPoint mapToCanvasPos(const QPoint& pos) const;
    void setScaledCanvas(QLabel* label, const QPixmap &pixmap);
    void setScaledButton(QPushButton* label, const QPixmap &pixmap);
    void updateUIForNewFrame(int frameIndex);
    QImage createImageFromFrame(const Frame &frame);
    void updateUIForSelectedFrame(int frameIndex);
    void deleteFrame(int frameIndex);
    void updateFrameIndices();
    QPixmap getPixMap(Frame frame);
    void showTutorialPopup();
    void darkModeClicked(int);
    void largeTextClicked(int);
    void saveFile();
    void loadFile();
    void updateAllThumbnails();
};

#endif // MAINWINDOW_H
