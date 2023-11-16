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

/**
 * @class FileManager
 * @brief The FileManager class represents the save and load features of the sprite editor.
 * It helps to take a vector of Frame objects and save it as Json within a sprite file, and
 * it also assists in loading a sprite file by converting it back to a vector of Frames.
 */
class FileManager : public QObject
{
    Q_OBJECT

private:
    /// @brief Object in which Json is written into
    QJsonObject writeJson;

    /// @brief Model that is utilized for color
    Model model;

public:
    /// @brief Constructor for the FileManager
    FileManager(QObject *parent = nullptr);

public slots:
    /// @brief Converts vector of Frames into Json stored in a sprite file
    /// @param vector<Frame> Vector of Frames which will be written into a sprite file
    /// @param QString The path where the sprite file will be saved
    void exportJson(std::vector<Frame>, QString);

    /// @brief Converts Json within sprite file into vector of Frames
    /// @param QString The path where the sprite file will be loaded
    /// @return Vector of Frames that contains the new data from loaded sprite file
    std::vector<Frame> importJson(QString);

signals:
    /// @brief Signal that emits when any error occurs saving or loading
    /// @param QString Error message
    void errorMessage(QString);
};

#endif // FILEMANAGER_H
