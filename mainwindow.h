#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include <QAbstractButton>

#include "model.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_addFrameButton_clicked();
    void setRed();
    void setBlue();

private:
    Ui::MainWindow *ui;
    QImage image;
    QPixmap pix;
    Model model;

    void updateImageAndPixMap(const pair<int,int> &pixmapMousePos);
    void setScaledPixmap(QLabel* label, const QPixmap &pixmap);
    void onToolButtonClicked(int id);

};
#endif // MAINWINDOW_H
