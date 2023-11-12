#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include <QAbstractButton>
#include <QPushButton>

#include "model.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///@brief Default constructor for main window
    MainWindow(QWidget *parent = nullptr);
    ///@brief Destructor for main window
    ~MainWindow();
    ///@brief Get the pixel coordinates for the mouse press and updates the canvas accordingly
    void mousePressEvent(QMouseEvent *event) override;
    ///@brief If pressed down, get the pixel coordinates for the mouse location and updates the canvas accordingly
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    ///@brief Create a new frame and update the UI accordingly
    void addFrameClicked();
    ///@brief Handles the selection of a specific frame and update the UI accordingly
    void handleFrameClicked();
    ///@brief Set the RGB of the currently selected color and update the UI accordingly
    void setRGB();

private:
    Ui::MainWindow *ui;
    QImage image;
    QPixmap pix;
    Model model;
    int frameCounter;

    void updateImageAndPixMap(const pair<int,int> &pixmapMousePos);
    void setScaledPixmap(QLabel* label, const QPixmap &pixmap);
    void setScaledButton(QPushButton* label, const QPixmap &pixmap);
    ///@brief Update the tool being used based on the button that was pressed
    void onToolButtonClicked(int id);

};
#endif // MAINWINDOW_H
