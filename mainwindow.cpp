#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(16, 16);
    pix.fill(QColor(255, 155, 155, 155));

    QImage image = pix.toImage();
    image.setPixelColor(8, 8, QColorConstants::Red);
    image.setPixelColor(3, 7, QColorConstants::Blue);
    pix.convertFromImage(image);

    ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

