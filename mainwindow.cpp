#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frame.h"
#include <QButtonGroup>
#include <QScrollBar>

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

    ui->scrollArea->verticalScrollBar()->setEnabled(false);

    // Connect the RGB spin box signals to the setRGB slot
    connect(ui->redSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
    connect(ui->blueSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
    connect(ui->greenSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    ui->nameEntryBox->clearFocus();
    ui->spinBox->clearFocus();
    QPoint pixmapMousePos = event->pos() - ui->pixMapLabel->mapTo(this, QPoint(0, 0));
    pair<int, int> pairMousePos(pixmapMousePos.x(), pixmapMousePos.y());
    updateImageAndPixMap(pairMousePos);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint pixmapMousePos = event->pos() - ui->pixMapLabel->mapTo(this, QPoint(0, 0));
    pair<int, int> pairMousePos(pixmapMousePos.x(), pixmapMousePos.y());
    updateImageAndPixMap(pairMousePos);
}

void MainWindow::updateImageAndPixMap(const pair<int, int> &pixmapMousePos) {
    // Checks if mouse position is within the QLabel pixmap
    if (0 <= pixmapMousePos.first && pixmapMousePos.first < ui->pixMapLabel->width() &&
        0 <= pixmapMousePos.second && pixmapMousePos.second < ui->pixMapLabel->height()) {
        // Use the scaling factor to determine the pixel position.
        int pixmapX = pixmapMousePos.first / (ui->pixMapLabel->width() / pix.width());
        int pixmapY = pixmapMousePos.second / (ui->pixMapLabel->height() / pix.height());

        // Set the pixel color to the model's selected color
        image.setPixelColor(pixmapX, pixmapY, model.getSelectedColor());
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

        // re-enable the color selection and reset the color to the one stored in the spin boxes
        ui->redSpin->setEnabled(true);
        ui->blueSpin->setEnabled(true);
        ui->greenSpin->setEnabled(true);

        // Pen tool was selected - do stuff with model
        setRGB();
    }
    else if(id == 2)
    {
        ui->mirrorTool->setEnabled(false);

        ui->redSpin->setEnabled(false);
        ui->blueSpin->setEnabled(false);
        ui->greenSpin->setEnabled(false);

        // Erase tool was selected - do stuff with model
        // Set model selected color to the background color
        model.setSelectedColor(QColor::fromRgb(64, 64, 64));
    }
}

void MainWindow::setRGB() {
    int red = ui->redSpin->value();
    int green = ui->greenSpin->value();
    int blue = ui->blueSpin->value();
    QColor newColor = *new QColor(red, green, blue);
    model.setSelectedColor(newColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addFrameButton_clicked()
{
    Frame frame(16);
    frame.SetColor(pair<int,int>(1, 3), QColor::fromRgb(0, 0, 0));
    QLabel *frameLabel = new QLabel();
    frameLabel->setMinimumWidth(50);
    frameLabel->setMinimumHeight(50);
    frameLabel->setMaximumHeight(50);
    frameLabel->setMinimumHeight(50);
    frameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->scrollArea->setMaximumWidth(ui->scrollArea->maximumWidth() + 70);
    ui->scrollArea->widget()->layout()->addWidget(frameLabel);
    setScaledPixmap(frameLabel, pix);
}
