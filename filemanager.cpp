#include <filemanager.h>
#include <iostream>

FileManager::FileManager(QObject *parent) : QObject{parent} {}

void FileManager::exportJson(std::vector<Frame> frames, QString docName) {
    int frameCounter = 0;
    writeJson["frameTotal"] = (int) frames.size();
    writeJson["frameDimension"] = frames.at(0).getSize();
    QJsonObject frameCollection;
    for (Frame frame : frames) {
        QMap<std::pair<int, int>, QColor> pixels = frame.getPixelMap();
        QJsonArray pixelCollection;
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
    writeJson.insert("frameCollection", frameCollection);
    QFile exportFile(docName);
    if (!exportFile.open(QIODevice::WriteOnly))
    {
        std::cout << "File failed to save" << std::endl;
        //emit errorMessage("File failed to save");
        return;
    }
    QJsonDocument document(writeJson);
    exportFile.write(document.toJson());
}

std::vector<Frame> FileManager::importJson(QString docName) {
    try {
        QFile importFile(docName);
        if (!importFile.open(QIODevice::ReadOnly)) {
            std::cout << "File failed to load" << std::endl;
            //emit errorMessage("File failed to load");
        }
        QByteArray dataArray = importFile.readAll();
        QJsonObject dataObject = QJsonDocument::fromJson(dataArray).object();
        int frameTotal = dataObject["frameTotal"].toInt();
        int frameDimension = dataObject["frameDimension"].toInt();
        QJsonObject frameCollection = dataObject.value("frameCollection").toObject();
        std::vector<Frame> frames;
        for (int frameCounter = 0; frameCounter < frameTotal; frameCounter++) {
            QJsonArray rows = frameCollection.value("frameNum" + QString::number(frameCounter)).toArray();
            Frame frame(frameDimension);
            QMap<std::pair<int, int>, QColor> pixelCollection;
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
        return frames;
    }
    catch (...) {
        std::cout << "File failed to load" << std::endl;
        //emit errorMessage("File failed to load");
    }
}
