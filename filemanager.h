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

class FileManager : public QObject
{
    Q_OBJECT
private:
    QJsonObject writeJson;
    Model model;

public:
    FileManager(QObject *parent = nullptr);

public slots:
    void exportJson(std::vector<Frame>, QString);
    std::vector<Frame> importJson(QString);
signals:
    void errorMessage(QString);
};

#endif // FILEMANAGER_H
