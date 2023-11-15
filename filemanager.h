/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * This project helps to demonstrate some C++ conventions in regards
 * to the topic of a FileManager class which has been splitted into a header
 * file. It assists in declarations of the FileManager object, functions, etc.
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <cmath>
#include "frame.h"
#include "model.h"

/**
 * @brief The FileManager class handles the import and export of frames in JSON format.
 * It uses a QJsonObject to store JSON data and communicates with the Model class to perform operations.
 */
class FileManager : public QObject {
    Q_OBJECT
private:
    /// @brief The QJsonObject used to write JSON data.
    QJsonObject writeJson;

    /// @brief The Model object used to interact with frame data.
    Model model;

public:
    /// @brief Constructor for the FileManager class.
    /// @param parent The parent QObject.
    FileManager(QObject *parent = nullptr);

public slots:
    /// @brief Export frames to a JSON file.
    /// @param frames The vector of frames to export.
    /// @param filePath The file path to save the JSON file.
    void exportJson(std::vector<Frame> frames, QString filePath);

    /// @brief Import frames from a JSON file.
    /// @param filePath The file path to the JSON file.
    /// @return The vector of frames imported from the JSON file.
    std::vector<Frame> importJson(QString filePath);

signals:
    /// @brief Signal emitted when an error message needs to be displayed.
    /// @param message The error message to display.
    void errorMessage(QString message);
};

#endif // FILEMANAGER_H
