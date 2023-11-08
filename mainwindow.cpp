#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pix(16, 16)
{
    ui->setupUi(this);
//    QPixmap pix(16, 16);
    pix.fill(QColorConstants::Black);

    image = pix.toImage();
    image.setPixelColor(8, 8, QColorConstants::Red);
    image.setPixelColor(3, 7, QColorConstants::Blue);
    image.setPixelColor(15, 15, QColorConstants::Blue);
    pix.convertFromImage(image);

    ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));

    cout << "Pixmap size: " << pix.width() << ", " << pix.height() << endl;
    cout << "Label size: " << ui->pixMapLabel->width() << ", " << ui->pixMapLabel->height() << endl;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Get the mouse position within the QLabel.
    QPoint globalMousePos = event->pos();

    // Map the mouse position to the pixmap's coordinates.
    QPoint pixmapMousePos = globalMousePos - ui->pixMapLabel->mapTo(this, QPoint(0, 0));

    // Checks if mouse position is within the QLabel pixmap
    if (0 <= pixmapMousePos.x() && pixmapMousePos.x() < ui->pixMapLabel->width() &&
        0 <= pixmapMousePos.y() && pixmapMousePos.y() < ui->pixMapLabel->height()) {
        // Use the scaling factor to determine the pixel position.
        int pixmapX = pixmapMousePos.x() / (ui->pixMapLabel->width() / pix.width());
        int pixmapY = pixmapMousePos.y() / (ui->pixMapLabel->height() / pix.height());

        // Temporary hard coded color red
        image.setPixelColor(pixmapX, pixmapY, QColorConstants::Red);
        pix.convertFromImage(image);
        ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));

        std::cout << "Mouse Pressed on Pixmap at Position: " << pixmapX << ", " << pixmapY << std::endl;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    // Get the mouse position within the QLabel.
    QPoint globalMousePos = event->pos();

    // Map the mouse position to the pixmap's coordinates.
    QPoint pixmapMousePos = globalMousePos - ui->pixMapLabel->mapTo(this, QPoint(0, 0));

    // Checks if mouse position is within the QLabel pixmap
    if (0 <= pixmapMousePos.x() && pixmapMousePos.x() < ui->pixMapLabel->width() &&
        0 <= pixmapMousePos.y() && pixmapMousePos.y() < ui->pixMapLabel->height()) {
        // Use the scaling factor to determine the pixel position.
        int pixmapX = pixmapMousePos.x() / (ui->pixMapLabel->width() / pix.width());
        int pixmapY = pixmapMousePos.y() / (ui->pixMapLabel->height() / pix.height());

        // Temporary hard coded color red
        image.setPixelColor(pixmapX, pixmapY, QColorConstants::Red);
        pix.convertFromImage(image);
        ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));

        std::cout << "Mouse Pressed on Pixmap at Position: " << pixmapX << ", " << pixmapY << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
