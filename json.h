#ifndef JSON_H
#define JSON_H

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>

#include "notepad.h"

class json
{
public:
    json();

    QString getJsonValue(QJsonObject jsonObj, QString key);

    QString themeSelect(QJsonObject jsonObj);

    QJsonObject jsonFile();

    void writeJson(QString jsonPath);

    QJsonObject readJson(QString jsonPath);

    QJsonObject checkAndCreateFolder();

    void dataWriteOnJson(QString key, QString value);

private:
    notepad* Notepad;

};

#endif // JSON_H
