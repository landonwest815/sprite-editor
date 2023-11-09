#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , image(16, 16, QImage::Format_RGB32)
{
    ui->setupUi(this);

    // set a fresh canvas
    image.fill(QColor::fromRgb(64, 64, 64));
    pix.convertFromImage(image);
    setScaledPixmap(ui->pixMapLabel, pix);
    setScaledPixmap(ui->previewLabel, pix);
    setScaledPixmap(ui->frameLabel, pix);

    cout << "Pixmap size: " << pix.width() << ", " << pix.height() << endl;
    cout << "Label size: " << ui->pixMapLabel->width() << ", " << ui->pixMapLabel->height() << endl;

    // Create a new button group
    QButtonGroup* toolButtonGroup = new QButtonGroup(this);

    // Add buttons to the group with IDs
    toolButtonGroup->addButton(ui->penTool, 1);
    toolButtonGroup->addButton(ui->eraseTool, 2);

    // Set the button group to exclusive
    toolButtonGroup->setExclusive(true);

    // Set pen as default tool
    ui->penTool->setChecked(true);
    onToolButtonClicked(1);

    // Connect the button clicked signal to your slot if needed
    connect(toolButtonGroup, &QButtonGroup::idClicked,
            this, &MainWindow::onToolButtonClicked);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    ui->lineEdit->clearFocus();
    ui->spinBox->clearFocus();
    QPoint pixmapMousePos = event->pos() - ui->pixMapLabel->mapTo(this, QPoint(0, 0));
    updateImageAndPixMap(pixmapMousePos);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint pixmapMousePos = event->pos() - ui->pixMapLabel->mapTo(this, QPoint(0, 0));
    updateImageAndPixMap(pixmapMousePos);
}

void MainWindow::updateImageAndPixMap(const QPoint &pixmapMousePos) {
    // Checks if mouse position is within the QLabel pixmap
    if (0 <= pixmapMousePos.x() && pixmapMousePos.x() < ui->pixMapLabel->width() &&
        0 <= pixmapMousePos.y() && pixmapMousePos.y() < ui->pixMapLabel->height()) {
        // Use the scaling factor to determine the pixel position.
        int pixmapX = pixmapMousePos.x() / (ui->pixMapLabel->width() / pix.width());
        int pixmapY = pixmapMousePos.y() / (ui->pixMapLabel->height() / pix.height());

        // Temporary hard coded color black
        image.setPixelColor(pixmapX, pixmapY, QColorConstants::Black);
        pix.convertFromImage(image);
        ui->pixMapLabel->setPixmap(pix.scaled(ui->pixMapLabel->size(), Qt::KeepAspectRatio));
        ui->previewLabel->setPixmap(pix.scaled(ui->previewLabel->size(), Qt::KeepAspectRatio));
        ui->frameLabel->setPixmap(pix.scaled(ui->frameLabel->size(), Qt::KeepAspectRatio));

        std::cout << "Mouse Pressed on Pixmap at Position: " << pixmapX << ", " << pixmapY << std::endl;
    }
}

void MainWindow::setScaledPixmap(QLabel* label, const QPixmap &pixmap) {
    label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
}

void MainWindow::onToolButtonClicked(int id) {
    if(id == 1)
    {
        ui->mirrorTool->setEnabled(true);

        // Pen tool was selected - do stuff with model
    }
    else if(id == 2)
    {
        ui->mirrorTool->setEnabled(false);

        // Erase tool was selected - do stuff with model
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
