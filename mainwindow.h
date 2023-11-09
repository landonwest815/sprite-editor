#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include <QAbstractButton>

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

private:
    Ui::MainWindow *ui;
    QImage image;
    QPixmap pix;

    void updateImageAndPixMap(const QPoint &pixmapMousePos);
    void setScaledPixmap(QLabel* label, const QPixmap &pixmap);
    void onToolButtonClicked(int id);

};
#endif // MAINWINDOW_H
