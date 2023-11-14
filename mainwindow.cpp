/************************
 *Main Window Class
 *Project: Sprite Editor
 *Assignment: A8 Sprite Editor Implementation
 *Team Geoff
 *Description: Gets data from the internal model and displays it to the UI. Also allows the user to update the model through the UI.
 * **********************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frame.h"
#include <QButtonGroup>
#include <QScrollBar>
#include <ostream>
#include <QTimer>
#include <QPropertyAnimation>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    image(16, 16, QImage::Format_RGB32), model(), frameCounter(1) {
        ui->setupUi(this);
        initializeUI();
        setupConnections();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeUI() {

    // Create an initial frame and display it
    addFrameClicked();
    updateUIForSelectedFrame(0);

    // Configure the tools
    toolButtonGroup = new QButtonGroup(this);
    toolButtonGroup->addButton(ui->penTool, 1);
    toolButtonGroup->addButton(ui->eraseTool, 2);
    toolButtonGroup->setExclusive(true);
    ui->penTool->setChecked(true);
    onToolButtonClicked(1);

    // Disable vertical scroll bar for a nicer visual
    ui->scrollArea->verticalScrollBar()->setEnabled(false);
}

void MainWindow::setupConnections() {
    // Tool buttons
    connect(toolButtonGroup, &QButtonGroup::idClicked,
            this, &MainWindow::onToolButtonClicked);

    // RGB Spin Boxes
    connect(ui->redSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
    connect(ui->blueSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
    connect(ui->greenSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);

    // Frame addition
    connect(ui->addFrameButton, &QPushButton::clicked,
            this, &MainWindow::addFrameClicked);

    // changes the value of frame counter.
    connect(ui->selectFPS, &QAbstractSlider::valueChanged,
            this, &MainWindow::onSelectFPS);

    //this should start animation process
    connect(ui->animateButton, &QPushButton::clicked,
            this, &MainWindow::onAnimateButtonClicked);
}

void MainWindow::updateAllPixmaps() {

    // Pull the image from the currently selected frame
    image = createImageFromFrame(model.getCurrentFrame());
    pix.convertFromImage(image);

    // Display it
    setScaledCanvas(ui->pixMapLabel, pix);
    setScaledCanvas(ui->previewLabel, pix);

    // Update the Frame thumbnail
    setScaledButton(frameThumbnails[model.getCurrentFrameIndex()], pix);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    clearFocusOnWidgets(); // visual purposes
    QPoint pos = mapToCanvasPos(event->pos());
    if (isValidCanvasPos(pos)) {
        updateImageAndCanvas(pos);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint pos = mapToCanvasPos(event->pos());
    if (isValidCanvasPos(pos)) {
        updateImageAndCanvas(pos);
    }
}

bool MainWindow::isValidCanvasPos(const QPoint& pos) const {
    return pos.x() >= 0 && pos.x() < ui->pixMapLabel->width() &&
           pos.y() >= 0 && pos.y() < ui->pixMapLabel->height();
}

QPoint MainWindow::mapToCanvasPos(const QPoint& pos) const {
    return pos - ui->pixMapLabel->mapToParent(QPoint(0, 0));
}

void MainWindow::updateImageAndCanvas(const QPoint& pos) {

    // Convert the position to the image's scale
    int pixmapX = static_cast<int>(pos.x() * (static_cast<double>(model.getCurrentFrame().getSize()) / ui->pixMapLabel->width()));
    int pixmapY = static_cast<int>(pos.y() * (static_cast<double>(model.getCurrentFrame().getSize()) / ui->pixMapLabel->height()));

    // Ensure the coordinates are within the bounds of the image
    if (pixmapX >= 0 && pixmapX < image.width() && pixmapY >= 0 && pixmapY < image.height()) {

        // Set the pixel color at the scaled position
        QColor selectedColor = model.getSelectedColor();
        model.getCurrentFrame().SetColor(std::make_pair(pixmapX, pixmapY), selectedColor);

        // Draw a square based on the tool size if applicable
        int toolSize = ui->toolSizeSpin->value();
        for (int dx = -toolSize / 2; dx <= toolSize / 2; ++dx) {
            for (int dy = -toolSize / 2; dy <= toolSize / 2; ++dy) {
                int toolX = pixmapX + dx;
                int toolY = pixmapY + dy;
                // Check bounds again for the tool size
                if (toolX >= 0 && toolX < image.width() && toolY >= 0 && toolY < image.height()) {
                    model.getCurrentFrame().SetColor(std::make_pair(toolX, toolY), selectedColor);
                }
            }
        }

        // Update the displayed UI
        updateAllPixmaps();
    }
}

void MainWindow::setRGB() {
    QColor newColor(ui->redSpin->value(), ui->greenSpin->value(), ui->blueSpin->value());
    model.setSelectedColor(newColor);
}

void MainWindow::onToolButtonClicked(int id) {
    if (id == 1) {
        model.setSelectedColor(QColor::fromRgb(ui->redSpin->value(), ui->greenSpin->value(), ui->blueSpin->value()));
    } else {
        model.setSelectedColor(QColor::fromRgb(64, 64, 64)); // erase by drawing with background color
    }
}

void MainWindow::addFrameClicked() {

    // Add a new frame to the model
    model.addNewFrame();

    // Set the current frame
    int newFrameIndex = model.getAllFrames().size() - 1;
    model.setCurrentFrame(newFrameIndex);

    // Update the UI to reflect the addition of the new frame
    updateUIForNewFrame(newFrameIndex);
}

void MainWindow::handleFrameClicked() {
    QPushButton *clickedFrameButton = qobject_cast<QPushButton*>(sender());
    if (clickedFrameButton) {
        int frameIndex = clickedFrameButton->text().toInt() - 1;
        model.setCurrentFrame(frameIndex);
        updateUIForSelectedFrame(frameIndex);
    }
}

void MainWindow::setScaledCanvas(QLabel* label, const QPixmap &pixmap) {
    label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
}

void MainWindow::clearFocusOnWidgets() {
    ui->nameEntryBox->clearFocus();
    ui->toolSizeSpin->clearFocus();
}

void MainWindow::updateUIForNewFrame(int frameIndex) {

    // Retrieve the new frame from the model
    Frame newFrame = model.getAllFrames().at(frameIndex);

    // Create a button for the new frame
    QPushButton *frameButton = new QPushButton(QString::number(frameCounter));
    frameCounter++;

    frameThumbnails[frameIndex] = frameButton;

    // Connect the button click signal to the frame selection handler
    connect(frameButton, &QPushButton::clicked, this, &MainWindow::handleFrameClicked);

    // Configure and add the new button to the UI
    frameButton->setMinimumSize(65, 55);
    frameButton->setMaximumSize(65, 55);
    frameButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->scrollArea->widget()->layout()->addWidget(frameButton);

    // Adjust the scroll area for nice looking spacing purposes
    ui->scrollArea->setMaximumWidth(ui->scrollArea->maximumWidth() + 85);

    // Set the button icon to the pixmap representing the new frame
    QImage frameImage = createImageFromFrame(newFrame);
    pix.convertFromImage(frameImage);
    setScaledButton(frameButton, pix);

    // Update the rest of the UI
    updateAllPixmaps();
}

void MainWindow::updateUIForSelectedFrame(int frameIndex) {

    // Get a reference to the selected frame
    Frame selectedFrame = model.getAllFrames().at(frameIndex);

    // Update the current frame in the model
    model.setCurrentFrame(frameIndex);

    // Create an image from the frame's pixel data
    QImage frameImage = createImageFromFrame(selectedFrame);

    // Update the pixMap with it
    pix.convertFromImage(frameImage);

    updateAllPixmaps();

   // highlightSelectedFrameThumbnail(frameIndex);
}

QImage MainWindow::createImageFromFrame(const Frame &frame) {

    // Create an image of the correct size
    int size = frame.getSize(); // length = width
    QImage frameImage(size, size, QImage::Format_ARGB32);

    // Get the map of pixels from the frame
    QMap<std::pair<int,int>, QColor> pixelMap = frame.getPixelMap();

    // Loop through each pixel and set the color to the image
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            std::pair<int, int> coord = std::make_pair(x, y);
            frameImage.setPixelColor(x, y, pixelMap.value(coord));
        }
    }

    return frameImage;
}

void MainWindow::setScaledButton(QPushButton* button, const QPixmap &pixmap) {
    button->setIcon(pixmap.scaled(button->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
    button->setIconSize(button->size());
}

void MainWindow::onSelectFPS(int FPS){
    frameCounter = 1000/FPS;
    qDebug() << "frame counter set to: " << frameCounter;
}

void MainWindow::onAnimateButtonClicked()
{
    qDebug() << "animation should start";
//    static vector<QPixmap> pixmaps = getPixMaps(model.getAllFrames());
    connect(&timer, &QTimer::timeout,
            this, &MainWindow::updatePreviewWindow);

    timer.start(frameCounter);
}

//vector<QPixmap> MainWindow::getPixMaps(vector<Frame> frames){
//    qDebug() << "executed getPixMaps";
//    vector<QPixmap> pixMaps;
//    for(size_t i = 0; i < frames.size(); i++){
//        // Create an image from the frame's pixel data
//        Frame currentFrame = frames.at(i);
//        QImage frameImage = createImageFromFrame(currentFrame);
//        QPixmap framePixMap;

//        framePixMap.convertFromImage(frameImage);
//        pixMaps.push_back(framePixMap);
//    }

//    return pixMaps;
//}

QPixmap MainWindow::getPixMap(Frame frame){
    QImage frameImage = createImageFromFrame(frame);
    QPixmap framePixMap;
    framePixMap.convertFromImage(frameImage);
    return framePixMap;
}

void MainWindow::updatePreviewWindow(){
    static int i = 0;
    QPixmap pixmap(getPixMap(model.getAllFrames().at(i)));

    ui->previewLabel->setPixmap(pixmap);

    setScaledCanvas(ui->previewLabel, pixmap);
}


