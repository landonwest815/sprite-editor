#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , image(16, 16, QImage::Format_RGB32)
{
    ui->setupUi(this);

    image.fill(QColor::fromRgb(64, 64, 64));

    // CHECKERBOARD BACKGROUND
//    for (int x = 0; x < image.width(); ++x) {
//        for (int y = 0; y < image.height(); ++y) {
//            // Calculate whether to color the pixel black or gray based on its position
//            if ((x + y) % 2 == 0) {
//                // Even sum of coordinates: color the pixel black
//                image.setPixelColor(x, y, QColor::fromRgb(160, 160, 160));
//            } else {
//                // Odd sum of coordinates: color the pixel gray
//                image.setPixelColor(x, y, QColor::fromRgb(128, 128, 128));
//            }
//        }
//    }

    pix.convertFromImage(image);

    ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));
    ui->previewLabel->setPixmap(pix.scaled(ui->previewLabel->size(), Qt::KeepAspectRatio));

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
        image.setPixelColor(pixmapX, pixmapY, QColorConstants::Black);
        pix.convertFromImage(image);
        ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));
        ui->previewLabel->setPixmap(pix.scaled(ui->previewLabel->size(), Qt::KeepAspectRatio));

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
        image.setPixelColor(pixmapX, pixmapY, QColorConstants::Black);
        pix.convertFromImage(image);
        ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));
        ui->previewLabel->setPixmap(pix.scaled(ui->previewLabel->size(), Qt::KeepAspectRatio));


        std::cout << "Mouse Pressed on Pixmap at Position: " << pixmapX << ", " << pixmapY << std::endl;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    pix.convertFromImage(image);
    ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));
}
MainWindow::~MainWindow()
{
    delete ui;
}
