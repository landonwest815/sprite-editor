#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frame.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * Gets data from the internal model and displays it to the UI. Also allows the user
 * to update the model through the UI.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    image(16, 16, QImage::Format_RGB32), model(), frameCounter(0), FPS(1000), animatingPreview(false), darkMode(false), speech(false) {
    ui->setupUi(this);
    file = new FileManager();
    initializeUI();
    setupConnections();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::askForFrameSize() {
    frameSizeDialog = new QDialog(this);
    int width = 400;
    frameSizeDialog->setFixedSize(width, 300);

    QLabel *titleLabel = new QLabel("Select Canvas Size:", frameSizeDialog);
    titleLabel->setFixedWidth(width);
    titleLabel->setFixedHeight(150);
    titleLabel->setStyleSheet("color: white; font-family: 'Segoe UI'; font-size: 18pt; font-weight: bold; font-style: italic;");
    titleLabel->setAlignment(Qt::AlignCenter);

    sizeComboBox = new QComboBox(frameSizeDialog);
    sizeComboBox->addItems({"4x4", "8x8", "16x16", "32x32", "64x64"});
    sizeComboBox->setStyleSheet(
        "QComboBox {"
        "    background-color: rgb(86, 86, 86);"
        "    color: white;"
        "    border: 1px solid gray;"
        "    border-radius: 3px;"
        "    padding: 1px 18px 1px 3px;"
        "    min-width: 6em;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 15px;"
        "    border-left-width: 1px;"
        "    border-left-color: darkgray;"
        "    border-left-style: solid;"
        "    border-top-right-radius: 3px;"
        "    border-bottom-right-radius: 3px;"
        "}"
        "QComboBox::down-arrow {"
        "    image: url(:/icons/Assets/Assets/dots.png);" // Use a smaller ellipsis icon
        "    width: 10px;" // Set the width as desired
        "    height: 10px;" // Set the height as desired
        "}"
        "QComboBox::down-arrow:on { /* when the combo box is open */"
        "    top: 1px;"
        "    left: 1px;"
        "}"
        "QComboBox QAbstractItemView {"
        "    color: white;"  // This sets the color of the text in the dropdown
        "}"
        );
        sizeComboBox->setFixedWidth(150);


    QPushButton *okButton = new QPushButton("OK", frameSizeDialog);
    connect(okButton, &QPushButton::clicked, frameSizeDialog, &QDialog::accept);
    okButton->setStyleSheet(
        "QPushButton {"
        "    background-color: rgb(86, 86, 86);"
        "    color: white;"
        "    border: 1px solid gray;"
        "    border-radius: 3px;"
        "    padding: 5px;"
        "    min-width: 6em;"
        "    text-align: center;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgb(96, 96, 96);" // Slightly lighter than the normal state
        "}"
        "QPushButton:pressed {"
        "    background-color: rgb(76, 76, 76);" // Slightly darker than the normal state
        "}"
        );
    QVBoxLayout *layout = new QVBoxLayout(frameSizeDialog);
    layout->addWidget(sizeComboBox);
    layout->addWidget(okButton);
    layout->setAlignment(Qt::AlignCenter);

    frameSizeDialog->setLayout(layout);

    if (frameSizeDialog->exec() == QDialog::Accepted) {
        int size = sizeComboBox->currentText().split("x").first().toInt();
        model.setFrameSize(size);
        qDebug() << "Frame size set to:" << size;
    } else {
        // Handle the case when the user cancels the input
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Information");
        msgBox.setText("Default frame size (16x16) will be used.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setStyleSheet("QLabel { color: white; }");
        msgBox.exec();

        model.setFrameSize(16);
    }

    // Update the UI with the initial frame
    model.setBackgroundColor(QColor::fromRgb(64, 64, 64));
    model.addNewFrame();

    // Set the current frame
    int newFrameIndex = model.getAllFrames().size() - 1;
    model.setCurrentFrame(newFrameIndex);

    // Update the UI to reflect the addition of the new frame
    updateUIForNewFrame(newFrameIndex);

    delete frameSizeDialog;  // Clean up the dialog after using it
}

void MainWindow::initializeUI() {
    // Create an initial frame and display it
    model.setBackgroundColor(QColor::fromRgb(64, 64, 64));
    askForFrameSize();

    // Configure the tools
    toolButtonGroup = new QButtonGroup(this);
    toolButtonGroup->addButton(ui->penTool, 1);
    toolButtonGroup->addButton(ui->eraseTool, 2);
    toolButtonGroup->setExclusive(true);
    ui->penTool->setChecked(true);
    onToolButtonClicked(1);

    // Connect the accessibility buttons to the required slots
    connect(ui->tutorialButton, &QPushButton::clicked, this, &MainWindow::showTutorialPopup);
    connect(ui->darkModeButton, &QPushButton::toggled, this ,&MainWindow::darkOrLightModeClicked);
    connect(ui->largeTextButton, &QPushButton::toggled, this ,&MainWindow::largeTextClicked);
    connect(ui->speechModeButton, &QPushButton::toggled, this ,&MainWindow::speechModeClicked);

    // Connect the save and load buttons to the required slots
    connect(ui->newButton, &QPushButton::clicked, this, &MainWindow::newProject);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadFile);

    // Connect filemanager signals to required slots
    connect(file, &FileManager::errorMessage, this, &MainWindow::showError);

    // Connect all button clicks to a speech slot
    QList<QPushButton*> allButtons = findChildren<QPushButton*>();
    for (QPushButton* button : allButtons) {
        connect(button, &QPushButton::clicked, this, &MainWindow::sayObjectName);
    }

    auto animationButtonGroup = new QButtonGroup(this);
    animationButtonGroup->addButton(ui->startAnimation, 1);
    animationButtonGroup->addButton(ui->stopAnimation, 2);
    animationButtonGroup->setExclusive(true);
    ui->startAnimation->setChecked(true);
    onSelectFPS(ui->fpsSlider->value());
    onAnimateButtonClicked();

    // Disable vertical scroll bar for a nicer visual
    ui->scrollArea->verticalScrollBar()->setEnabled(false);

    darkOrLightModeClicked();
}

void MainWindow::setupConnections() {
    // Tool buttons
    connect(toolButtonGroup, &QButtonGroup::idClicked,
            this, &MainWindow::onToolButtonClicked);

    // RGB Spin Boxes
    connect(ui->redSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
    connect(ui->blueSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);
    connect(ui->greenSpin, &QSpinBox::valueChanged, this, &MainWindow::setRGB);

    // Color Presets
    connect(ui->redPreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->greenPreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->bluePreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->yellowPreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->orangePreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->purplePreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->blackPreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->whitePreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    connect(ui->brownPreset, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);

    // Frame addition
    connect(ui->addFrameButton, &QPushButton::clicked,
            this, &MainWindow::addFrameClicked);

    connect(ui->duplicateFrameButton, &QPushButton::clicked,
            this, &MainWindow::duplicateFrameClicked);

    // Preview Animation
    connect(ui->fpsSlider, &QAbstractSlider::valueChanged,
            this, &MainWindow::onSelectFPS);

    connect(ui->startAnimation, &QPushButton::clicked,
            this, &MainWindow::onAnimateButtonClicked);

    connect(ui->stopAnimation, &QPushButton::clicked,
            this, &MainWindow::onStopAnimationClicked);

    connect(&timer, &QTimer::timeout,
            this, &MainWindow::updatePreviewWindow);

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

void MainWindow::updateAllThumbnails() {
    // Loop through all frames and update their thumbnails
    for (int i = 0; i < model.getNumberOfFrames(); ++i) {
        QImage frameImage = createImageFromFrame(model.getAllFrames().at(i));
        QPixmap framePixmap;
        framePixmap.convertFromImage(frameImage);
        setScaledButton(frameThumbnails[i], framePixmap);
    }
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
        model.getCurrentFrame().setColor(std::make_pair(pixmapX, pixmapY), selectedColor);

        mirrorPixel(pixmapX, pixmapY, selectedColor);

        // Draw a square based on the tool size if applicable
        int toolSize = ui->toolSizeSpin->value();
        for (int dx = -toolSize / 2; dx <= toolSize / 2; ++dx) {
            for (int dy = -toolSize / 2; dy <= toolSize / 2; ++dy) {
                int toolX = pixmapX + dx;
                int toolY = pixmapY + dy;
                // Check bounds again for the tool size
                if (toolX >= 0 && toolX < image.width() && toolY >= 0 && toolY < image.height()) {
                    model.getCurrentFrame().setColor(std::make_pair(toolX, toolY), selectedColor);
                    mirrorPixel(toolX, toolY, selectedColor);
                }
            }
        }

        // Update the displayed UI
        updateAllPixmaps();
    }
}

void MainWindow::mirrorPixel(int pixX, int pixY, QColor selectedColor) {
    // If mirror tool is active, do some math to mirror the x-position of the placed pixel
    if (ui->mirrorTool->isChecked()) {
        int mirrorX = 0;
        mirrorX = (image.width() - 1) - pixX;
        model.getCurrentFrame().setColor(std::make_pair(mirrorX, pixY), selectedColor);
    }
}

void MainWindow::setRGB() {
    QColor newColor(ui->redSpin->value(), ui->greenSpin->value(), ui->blueSpin->value());
    model.setSelectedColor(newColor);
}

void MainWindow::onToolButtonClicked(int id) {
    if (id == 1) {
        model.setSelectedColor(QColor::fromRgb(ui->redSpin->value(), ui->greenSpin->value(), ui->blueSpin->value()));
        // enable color selection
        ui->redSpin->setEnabled(true);
        ui->blueSpin->setEnabled(true);
        ui->greenSpin->setEnabled(true);
        ui->redPreset->setEnabled(true);
        ui->orangePreset->setEnabled(true);
        ui->yellowPreset->setEnabled(true);
        ui->greenPreset->setEnabled(true);
        ui->bluePreset->setEnabled(true);
        ui->purplePreset->setEnabled(true);
        ui->blackPreset->setEnabled(true);
        ui->brownPreset->setEnabled(true);
        ui->whitePreset->setEnabled(true);
    } else {
        model.setSelectedColor(model.getBackgroundColor()); // erase by drawing with background color
        // disable color selection
        ui->redSpin->setEnabled(false);
        ui->blueSpin->setEnabled(false);
        ui->greenSpin->setEnabled(false);
        ui->redPreset->setEnabled(false);
        ui->orangePreset->setEnabled(false);
        ui->yellowPreset->setEnabled(false);
        ui->greenPreset->setEnabled(false);
        ui->bluePreset->setEnabled(false);
        ui->purplePreset->setEnabled(false);
        ui->blackPreset->setEnabled(false);
        ui->brownPreset->setEnabled(false);
        ui->whitePreset->setEnabled(false);
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

void MainWindow::duplicateFrameClicked() {
    model.duplicateNewFrame(model.getCurrentFrame());

    // Set the current frame
    int newFrameIndex = model.getAllFrames().size() - 1;
    model.setCurrentFrame(newFrameIndex);

    // Update the UI to reflect the addition of the new frame
    updateUIForNewFrame(newFrameIndex);
}

void MainWindow::deleteFrame(int frameIndex) {

    // Create a fresh frame if last one
    if (model.getAllFrames().size() < 2) {
        addFrameClicked();
    }

    // Remove the frame from the model
    model.removeFrame(frameIndex);

    // Remove the corresponding thumbnail button
    QPushButton* frameButton = frameThumbnails.value(frameIndex);
    if (frameButton) {
        // remove it from the scroll view
        ui->scrollArea->widget()->layout()->removeWidget(frameButton->parentWidget());

        // delete it
        delete frameButton->parentWidget();
    }

    // Adjust the scroll area for nice looking spacing purposes
    ui->scrollArea->setMaximumWidth(ui->scrollArea->maximumWidth() - 110);

    // Remove the frame thumbnail from the map
    frameThumbnails.remove(frameIndex);

    // Update the frameCounter
    frameCounter--;

    updateFrameIndices();

    // Set the frame to the right as the current
    // unless it is the right most frame
    if (frameIndex == static_cast<int>(model.getAllFrames().size())) {
        frameIndex--;
    }
    model.setCurrentFrame(frameIndex);
    updateUIForSelectedFrame(frameIndex);
}

void MainWindow::updateFrameIndices() {
    // Loop over all frames and update their indices
    QMap<int, QPushButton*> newFrameThumbnails;
    int newIndex = 0;

    for (auto &button : frameThumbnails) {

        // get the container
        auto *frameContainer = button->parentWidget();

        // get the two children
        auto *frameButton = frameContainer->findChild<QPushButton*>("frameButton");
        auto *closeButton = frameContainer->findChild<QPushButton*>("closeButton");

        // update both
        frameButton->setText(QString::number(newIndex));
        closeButton->setProperty("frameIndex", newIndex);

        // update the map and increment
        newFrameThumbnails[newIndex] = frameButton;
        newIndex++;
    }

    frameThumbnails = newFrameThumbnails;
}

void MainWindow::handleFrameClicked() {
    QPushButton *clickedFrameButton = qobject_cast<QPushButton*>(sender());
    if (clickedFrameButton) {
        int frameIndex = clickedFrameButton->text().toInt();
        qDebug() << frameIndex;
        model.setCurrentFrame(frameIndex);
        updateUIForSelectedFrame(frameIndex);
    }
}

void MainWindow::setScaledCanvas(QLabel* label, const QPixmap &pixmap) {
    label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
}

void MainWindow::clearFocusOnWidgets() {
    ui->toolSizeSpin->clearFocus();
}

void MainWindow::updateUIForNewFrame(int frameIndex) {

    // Retrieve the new frame from the model
    Frame newFrame = model.getAllFrames().at(frameIndex);

    model.setCurrentFrame(frameIndex);

    QWidget *frameContainer = new QWidget;
    QGridLayout *layout = new QGridLayout(frameContainer);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create a button for the new frame
    QPushButton *frameButton = new QPushButton(QString::number(frameCounter));
    frameCounter++;

    if (darkMode) {
        frameButton->setStyleSheet("color: white;");
    } else {
        frameButton->setStyleSheet("color: black;");
    }

    frameButton->setMinimumSize(65, 55);
    frameButton->setMaximumSize(65, 55);
    frameButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    frameButton->setObjectName("frameButton");

    frameThumbnails[frameIndex] = frameButton;

    connect(frameButton, &QPushButton::clicked, this, &MainWindow::handleFrameClicked);

    QPushButton *closeButton = new QPushButton("X");
    closeButton->setProperty("frameIndex", frameIndex);
    closeButton->setFixedSize(15, 15); // Adjust size as needed
    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    closeButton->setObjectName("closeButton");

    if (darkMode) {
        closeButton->setStyleSheet("color: white;");
    } else {
        closeButton->setStyleSheet("color: black;");
    }

    connect(closeButton, &QPushButton::clicked, this, [this]() {
        QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
        if (senderButton) {
            int frameIndex = senderButton->property("frameIndex").toInt();
            deleteFrame(frameIndex);
        }
    });

    // Add the frame button to the layout, spanning 1 row and 1 column
    layout->addWidget(frameButton, 0, 0, 1, 1);

    // Add the close button in the top right corner, in the first row and second column
    layout->addWidget(closeButton, 0, 1, 1, 1, Qt::AlignTop | Qt::AlignRight);

    // Set alignment to ensure the "X" button stays in the top-right corner
    layout->setAlignment(closeButton, Qt::AlignTop | Qt::AlignRight);

    // Add the container to the UI
    ui->scrollArea->widget()->layout()->addWidget(frameContainer);

    // Adjust the scroll area for nice looking spacing purposes
    ui->scrollArea->setMaximumWidth(ui->scrollArea->maximumWidth() + 110);

    // Set the button icon to the pixmap representing the new frame
    QImage frameImage = createImageFromFrame(newFrame);
    pix.convertFromImage(frameImage);

    // Update the UI
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

    this->FPS = 1000/FPS;
    qDebug() << "frame counter set to: " << this->FPS;
    // resets the FPS on GUI
    if(animatingPreview){
        timer.start(this->FPS);
    }
}

void MainWindow::onAnimateButtonClicked()
{
    animatingPreview = true;
    qDebug() << "animation should start";
    timer.start(FPS);
}

QPixmap MainWindow::getPixMap(Frame frame){
    // gets pixmap for frame
    QImage frameImage = createImageFromFrame(frame);
    QPixmap framePixMap;
    framePixMap.convertFromImage(frameImage);
    return framePixMap;
}

void MainWindow::updatePreviewWindow(){
    static int i = 0;
    qDebug() << "showing frame: " << i;
    if (i < static_cast<int>(model.getAllFrames().size())) {
        QPixmap pixmap(getPixMap(model.getAllFrames().at(i)));
        ui->previewLabel->setPixmap(pixmap);
        setScaledCanvas(ui->previewLabel, pixmap);
        // this allows the animation to repeat until the timer is stopped.
        i = (i + 1) % model.getNumberOfFrames();
    }
}

void MainWindow::onStopAnimationClicked(){
    animatingPreview = false;
    timer.stop();
    updateAllPixmaps();
}

void MainWindow::showTutorialPopup() {
    QDialog* tutorialDialog = new QDialog(this);
    tutorialDialog->setWindowTitle("Tutorial Popup");
    QVBoxLayout* layout = new QVBoxLayout(tutorialDialog);
    QLabel* tutorialLabel = new QLabel(tutorialDialog);
    tutorialLabel->setPixmap(QPixmap(":/icons/Assets/Assets/tutorial.png"));
    layout->addWidget(tutorialLabel);
    tutorialDialog->exec();
}

void MainWindow::darkOrLightModeClicked() {
    if (darkMode) {
        darkMode = false;
        this->setStyleSheet("background-color: #fafafa;");



        QWidget* wigets[23] = {ui->darkModeLabel, ui->textSizeLabel, ui->textToSpeechLabel,
                               ui->tutorialLabel, ui->loadLabel, ui->saveLabel, ui->toolsLabel,
                               ui->drawLabel, ui->erase, ui->toolSettingLabel, ui->toolSizeLabel,
                               ui->redLabel, ui->redSpin, ui->greenLabel, ui->greenSpin, ui->blueLabel,
                               ui->blueSpin, ui->mirrorLabel, ui->animationLabel, ui->FPSLabel, ui->toolSizeSpin,
                               ui->titleLabel, ui->newLabl
                               };

        for (QWidget* widget : wigets) {
            widget->setStyleSheet("color: black");
        }

        QWidget* buttons[14] = { ui->addFrameButton, ui->duplicateFrameButton, ui->penTool,
                                ui->eraseTool, ui->mirrorTool, ui->startAnimation, ui->stopAnimation,
                                ui->saveButton, ui->loadButton, ui->tutorialButton, ui->darkModeButton,
                                ui->speechModeButton, ui->largeTextButton, ui->newButton};

        // sets the style sheet for the darkmode feature
        // first goes over the buttons
        for (QWidget* button : buttons) {
            button->setStyleSheet(R"(   QPushButton {
                                            background-color: #e6e6e6; /* Light grey background for light mode */
                                            color: black; /* Dark text for contrast */
                                            border-radius: 5px; /* Rounded corners with a radius of 5 pixels */
                                        }

                                        QPushButton:hover {
                                            background-color: #cccccc; /* Slightly darker grey for hover state */
                                        }

                                        QPushButton:pressed {
                                            background-color: #b3b3b3; /* Even darker grey for pressed state */
                                        }

                                        QPushButton:checked {
                                            background-color: #cccccc; /* Lighter grey color when button is checked */
                                        }
                                    )");
        }

        // then go over other elements of the GUI
        ui->tabWidget->setStyleSheet(R"(QTabWidget::tab-bar {
                                        alignment: center;
                                    }

                                    /* Style the tab itself */
                                    QTabBar::tab {
                                        background: #e6e6e6; /* Light grey background for light mode */
                                        color: black; /* Dark text color for contrast */
                                        padding: 5px; /* Space between text and edge */
                                        margin-left: 5px; /* Space between tabs */
                                        border-top-left-radius: 5px; /* Rounded top left corner */
                                        border-top-right-radius: 5px; /* Rounded top right corner */
                                        border-bottom-left-radius: 5px; /* Rounded bottom left corner */
                                        border-bottom-right-radius: 5px; /* Rounded bottom right corner */
                                    }

                                    /* Style the selected tab */
                                    QTabBar::tab:selected {
                                        background: #cccccc; /* A lighter shade for the selected tab */
                                    }

                                    QTabWidget::pane { /* The tab widget frame */
                                        border-top: 2px solid #C2C7CB;
                                        position: absolute;
                                        top: -0.5em;
                                    }
                                    )");

        model.setBackgroundColor(QColor::fromRgb(230, 230, 230));
        for (Frame& frame : model.getAllFrames()) {
            frame.toggleBackgroundColor(model.getBackgroundColor());
        }

        QWidget* sectionHeaders[4] = { ui->toolSettingLabel, ui->toolsLabel, ui->colorsLabel, ui->animationLabel };

        // sets the style sheet for the darkmode feature
        // first goes over the buttons
        for (QWidget* header : sectionHeaders) {
            header->setStyleSheet("QLabel {"
                                  "    background-color: rgb(230, 230, 230);" // A nice shade of dark gray
                                  "    color: black;" // White text color
                                  "    padding: 5px;" // Padding around the text
                                  "    border-radius: 4px;" // Rounded corners
                                  "    font-weight: bold;" // Bold font
                                  "    font-style: italic;" // Italic font style
                                  "    qproperty-alignment: 'AlignCenter';" // Center alignment for text
                                  "    margin-top: 2px;" // Space from the top margin
                                  "    margin-bottom: 2px;" // Space from the bottom margin
                                  "    border: 1px solid rgb(200, 200, 200);" // Border with a slightly lighter shade of gray
                                  "}");
        }

        updateUIForSelectedFrame(model.getCurrentFrameIndex());
        updateAllThumbnails();

        for (auto it = frameThumbnails.constBegin(); it != frameThumbnails.constEnd(); ++it) {
            it.value()->setStyleSheet("QPushButton { color: black; }");
            QPushButton* closeButton = it.value()->parentWidget()->findChild<QPushButton*>("closeButton");
            if (closeButton) {
                closeButton->setStyleSheet("QPushButton { color: black; }");
            }
        }

    }
    else {
        darkMode = true;
        this->setStyleSheet("background-color: #303030;");



        QWidget* wigets[23] = {ui->darkModeLabel, ui->textSizeLabel, ui->textToSpeechLabel,
            ui->tutorialLabel, ui->loadLabel, ui->saveLabel, ui->toolsLabel,
            ui->drawLabel, ui->erase, ui->toolSettingLabel, ui->toolSizeLabel,
            ui->redLabel, ui->redSpin, ui->greenLabel, ui->greenSpin, ui->blueLabel,
            ui->blueSpin, ui->mirrorLabel, ui->animationLabel, ui->FPSLabel, ui->toolSizeSpin,
            ui->titleLabel, ui->newLabl
        };
        for (QWidget* widget : wigets) {
            widget->setStyleSheet("color: white");
        }

        QWidget* buttons[14] = { ui->addFrameButton, ui->duplicateFrameButton, ui->penTool,
                                ui->eraseTool, ui->mirrorTool, ui->startAnimation, ui->stopAnimation,
                                ui->saveButton, ui->loadButton, ui->tutorialButton, ui->darkModeButton,
                                ui->speechModeButton, ui->largeTextButton, ui->newButton};

        // sets the style sheet for the darkmode feature
        // first goes over the buttons
        for (QWidget* button : buttons) {
            button->setStyleSheet(R"(   QPushButton {
                                            background-color: #646464; /* Dark grey background, matching the handle */
                                            color: white; /* Light text for contrast */
                                            border-radius: 5px; /* Rounded corners with a radius of 10 pixels */
                                        }

                                        QPushButton:hover {
                                            background-color: #505050; /* Slightly lighter grey for hover state */
                                        }

                                        QPushButton:pressed {
                                            background-color: #303030; /* Slightly darker grey for pressed state */
                                        }

                                        QPushButton:checked {
                                            background-color: #999999; /* Color when button is checked */
                                        }
                                    )");
        }

        //then modify other ui elements
        ui->tabWidget->setStyleSheet(R"(QTabWidget::tab-bar {
                                            alignment: center;
                                        }

                                        /* Style the tab itself */
                                        QTabBar::tab {
                                            background: #646464; /* Light gray background */
                                            color: white; /* Dark text color for contrast */
                                            padding: 5px; /* Space between text and edge */
                                            margin-left: 5px; /* Space between tabs */
                                            border-top-left-radius: 5px; /* Rounded top left corner */
                                            border-top-right-radius: 5px; /* Rounded top right corner */
                                           border-bottom-left-radius: 5px; /* Rounded top left corner */
                                            border-bottom-right-radius: 5px; /* Rounded top right corner */
                                        }

                                        /* Style the selected tab */
                                        QTabBar::tab:selected {
                                            background: #999999; /* A different shade for the selected tab */
                                        }

                                        QTabWidget::pane { /* The tab widget frame */
                                            border-top: 2px solid #C2C7CB;
                                            position: absolute;
                                            top: -0.5em;
                                        }
                                    )");

        model.setBackgroundColor(QColor::fromRgb(64, 64, 64));
        for (Frame& frame : model.getAllFrames()) {
            frame.toggleBackgroundColor(model.getBackgroundColor());
        }

        QWidget* sectionHeaders[4] = { ui->toolSettingLabel, ui->toolsLabel, ui->colorsLabel, ui->animationLabel };

        // sets the style sheet for the darkmode feature
        // first goes over the buttons
        for (QWidget* header : sectionHeaders) {
            header->setStyleSheet("QLabel {"
                                  "    background-color: rgb(64, 64, 64);" // A nice shade of dark gray
                                  "    color: white;" // White text color
                                  "    padding: 5px;" // Padding around the text
                                  "    border-radius: 4px;" // Rounded corners
                                  "    font-weight: bold;" // Bold font
                                  "    font-style: italic;" // Italic font style
                                  "    qproperty-alignment: 'AlignCenter';" // Center alignment for text
                                  "    margin-top: 2px;" // Space from the top margin
                                  "    margin-bottom: 2px;" // Space from the bottom margin
                                  "    border: 1px solid rgb(86, 86, 86);" // Border with a slightly lighter shade of gray
                                  "}");
        }

        updateUIForSelectedFrame(model.getCurrentFrameIndex());
        updateAllThumbnails();

        for (auto it = frameThumbnails.constBegin(); it != frameThumbnails.constEnd(); ++it) {
            it.value()->setStyleSheet("QPushButton { color: white; }");
            QPushButton* closeButton = it.value()->parentWidget()->findChild<QPushButton*>("closeButton");
            if (closeButton) {
                closeButton->setStyleSheet("QPushButton { color: white; }");
            }
        }

    }
    onToolButtonClicked(1);
}

void MainWindow::largeTextClicked(int toggled) {
    QFont largeFont("Segoe UI", 20);
    QFont regularFont("Segoe UI", 13);
    QString textOption[2] = {"Large Text", "Regular Text"};
    QFont fontSize[2] = {regularFont, largeFont};
    QWidget* wigets[22] = {ui->darkModeLabel, ui->textSizeLabel, ui->textToSpeechLabel,
                           ui->tutorialLabel, ui->loadLabel, ui->saveLabel, ui->toolsLabel,
                           ui->drawLabel, ui->erase, ui->toolSettingLabel, ui->toolSizeLabel,
                           ui->redLabel, ui->greenLabel, ui->blueLabel, ui->mirrorLabel,
                           ui->animationLabel, ui->FPSLabel, ui->newLabl, ui->toolSettingLabel,
                           ui->toolsLabel, ui->colorsLabel, ui->animationLabel};
    // after putting all widgets into array, loop through and set the text to what has been toggled.
    for (QWidget* widget : wigets) {
        widget->setFont(fontSize[toggled]);
    }
}

void MainWindow::saveFile() {
    QString saveFilePath = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "SSP Files (*.ssp)");
    if (!saveFilePath.isEmpty()) {
        if (!saveFilePath.endsWith(".ssp", Qt::CaseInsensitive)) {
            QMessageBox::information(this, "Save File Failed", "Please save the file with a .ssp extension.");
        } else {
            file->exportJson(model.getAllFrames(), saveFilePath);
        }
    } else {
        QMessageBox::information(this, "Save File Failed", "No save location selected. Please choose a valid location.");
    }
}

void MainWindow::loadFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open .ssp File", QDir::homePath(), "SSP Files (*.ssp);;All Files (*.*)");
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);
        if (fileInfo.suffix().toLower() == "ssp") {
            std::vector<Frame> newFrames = file->importJson(filePath);
            model.setAllFrames(newFrames);
            model.setFrameSize(newFrames.at(0).getSize());
            updateThumbnailsFromModel();
        } else {
            QMessageBox::information(this, "Load File Failed", "Selected file is not a .ssp file. Please choose a valid .ssp file.");
        }
    } else {
        QMessageBox::information(this, "Load File Failed", "No file selected. Please choose a .ssp file.");
    }
}

void MainWindow::updateThumbnailsFromModel() {
    // First, clear existing thumbnails
    for (QPushButton* button : std::as_const(frameThumbnails)) {
        ui->scrollArea->widget()->layout()->removeWidget(button->parentWidget());
        delete button->parentWidget();
    }
    frameThumbnails.clear();
    frameCounter = 0;

    // Then, create new thumbnails for all frames in the updated model
    for (int i = 0; i < model.getNumberOfFrames(); i++) {
        updateUIForNewFrame(i);
    }

    ui->scrollArea->setMaximumWidth(5 + 110 * model.getNumberOfFrames());

    // easy trick to adjust all the dark/light mode settings
    if (model.getNumberOfFrames() > 0) {
        darkOrLightModeClicked();
        darkOrLightModeClicked();
    }
}

void MainWindow::onColorButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        // colors corresponding to the buttons
        QHash<QPushButton*, QColor> colorHash;
        colorHash[ui->redPreset] = QColor(128, 0, 0);   // Dark red color
        colorHash[ui->greenPreset] = QColor(0, 128, 0); // Dark green color
        colorHash[ui->bluePreset] = QColor(0, 0, 128);  // Dark blue color
        colorHash[ui->orangePreset] = QColor(196, 128, 0);  // Dark orange color
        colorHash[ui->yellowPreset] = QColor(196, 196, 0);  // Dark yellow color
        colorHash[ui->purplePreset] = QColor(128, 0, 128);  // Dark purple color
        colorHash[ui->blackPreset] = QColor(0, 0, 0);  // Dark black color
        colorHash[ui->whitePreset] = QColor(255, 255, 255);  // Dark white color
        colorHash[ui->brownPreset] = QColor(78, 48, 26);  // Dark brown color


        // Check if the clicked button is one of the color buttons
        if (colorHash.contains(button)) {
            QColor newColor = colorHash[button];
            model.setSelectedColor(newColor);
            ui->redSpin->setValue(newColor.red());
            ui->greenSpin->setValue(newColor.green());
            ui->blueSpin->setValue(newColor.blue());
        }
    }
}

void MainWindow::speechModeClicked(int toggled) {
    if (toggled) {
        speech = true;

    } else {
        speech = false;
    }
}

void MainWindow::sayObjectName() {
    if(speech) {
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
        const QString name = clickedButton->objectName();
        say.say(name);
    }
}

void MainWindow::showError(QString msg) {
    QMessageBox::information(this, "Error", msg);
}

void MainWindow::newProject() {
    model.clearModel();
    updateThumbnailsFromModel();
    askForFrameSize();
    darkOrLightModeClicked();
    darkOrLightModeClicked();
}
