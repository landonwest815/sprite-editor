#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <cmath>
#include <frame.h>

class FileManager : public QObject
{
private:
    QJsonObject writeJson;

public:
    FileManager(QObject *parent = nullptr);

public slots:
    void exportJson(std::vector<Frame>, QString);
    std::vector<Frame> importJson(QString);
};

#endif // FILEMANAGER_H
