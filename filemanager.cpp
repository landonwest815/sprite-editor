#include "filemanager.h"
#include "model.h"

/**
 * Author(s):     Team Geoff:
 *                Ryan Nguyen (Taizuki), John Nguyen (johnguyn),
 *           	  Christian Hartman (Is-This-One-Avaiable), Caleb Funk (Funkyc02),
 *                Landon West (landonwest815), and Pablo Arancibia-Bazan (Pablo23117)
 * Course:        CS 3505, University of Utah, School of Computing
 * Assignment:    A8 - Sprite Editor Implementation
 * File Contents:
 * Used to manage Files using Json to be able to save and load a Sprite Editor Project.
 */

FileManager::FileManager(QObject *parent) : QObject{parent}, model() {}

void FileManager::exportJson(std::vector<Frame> frames, QString docName) {
    int frameCounter = 0;
    // Writes the amount and sizes of the frames to Json
    writeJson["frameTotal"] = (int) frames.size();
    writeJson["frameDimension"] = frames.at(0).getSize();
    QJsonObject frameCollection;
    // Creates a Json Frame for each one present in the vector
    for (Frame frame : frames) {
        QMap<std::pair<int, int>, QColor> pixels = frame.getPixelMap();
        QJsonArray pixelCollection;
        // Populates each Frame with the pixels and data associated with it
        for (auto pixel = pixels.begin(); pixel != pixels.end(); ++pixel) {
            QJsonArray infoCollection;
            infoCollection.push_back(pixel.key().first);
            infoCollection.push_back(pixel.key().second);
            infoCollection.push_back(pixel.value().red());
            infoCollection.push_back(pixel.value().green());
            infoCollection.push_back(pixel.value().blue());
            infoCollection.push_back(pixel.value().alpha());
            pixelCollection.push_back(infoCollection);
        }
        frameCollection.insert("frameNum" + QString::number(frameCounter), pixelCollection);
        frameCounter++;
    }
    // Writes the Json into a file and saves it at a desired location
    writeJson.insert("frameCollection", frameCollection);
    QFile exportFile(docName);
    // Returns and emits signal if file fails to save
    if (!exportFile.open(QIODevice::WriteOnly))
    {
        emit errorMessage("File failed to save");
        return;
    }
    QJsonDocument document(writeJson);
    exportFile.write(document.toJson());
}

std::vector<Frame> FileManager::importJson(QString docName) {
    try {
        // Loads the Json from a desired location into a object
        QFile importFile(docName);
        if (!importFile.open(QIODevice::ReadOnly)) {
            emit errorMessage("File failed to load");
        }
        QByteArray dataArray = importFile.readAll();
        QJsonObject dataObject = QJsonDocument::fromJson(dataArray).object();
        // Extracts amount and sizes of the frames to Json
        int frameTotal = dataObject["frameTotal"].toInt();
        int frameDimension = dataObject["frameDimension"].toInt();
        QJsonObject frameCollection = dataObject.value("frameCollection").toObject();
        std::vector<Frame> frames;
        // Creates a Frame for each one present in the Json data
        for (int frameCounter = 0; frameCounter < frameTotal; frameCounter++) {
            QJsonArray rows = frameCollection.value("frameNum" + QString::number(frameCounter)).toArray();
            Frame frame(frameDimension, model.getBackgroundColor());
            QMap<std::pair<int, int>, QColor> pixelCollection;
            // Populates each Frame with the pixels and data associated with it
            for(int rowIndex = 0; rowIndex < pow(frameDimension,2); rowIndex++)
            {
                QJsonArray pixels = rows.at(rowIndex).toArray();
                int xCoord = pixels.at(0).toInteger();
                int yCoord = pixels.at(1).toInteger();
                int colorR = pixels.at(2).toInteger();
                int colorG = pixels.at(3).toInteger();
                int colorB = pixels.at(4).toInteger();
                int colorA = pixels.at(5).toInteger();
                std::pair<int,int> coordinate(xCoord, yCoord);
                QColor color(colorR, colorG, colorB, colorA);
                pixelCollection.insert(coordinate, color);
            }
            frame.setPixelMap(pixelCollection);
            frames.push_back(frame);
        }
        // Returns the vector of Frames made from loaded sprite file
        return frames;
    }
    catch (...) {
        // Emits signal if file fails to load anywhere within the method
        emit errorMessage("File failed to load");
    }
}
