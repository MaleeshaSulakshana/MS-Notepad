#include "json.h"

json::json()
{

}

QString json::getJsonValue(QJsonObject jsonObj, QString key)
{           
    QString returnValue = jsonObj.find(key).value().toString();

    if (returnValue == ""){
        writeJson(Notepad->path("jsonName"));
        returnValue = jsonFile().find(key).value().toString();
    }

    return returnValue;
}

QString json::themeSelect(QJsonObject jsonObj)
{
    QString theme;
    QString jsonPath = Notepad->path("jsonName");

    QString color = getJsonValue(jsonObj, "Theme");
    QString fontColor = getJsonValue(jsonObj, "TextColor");

    if (color == "Dark"){
        theme = Notepad->themeColor(color, fontColor);
    }
    else if (color == "Light"){
        theme = Notepad->themeColor(color, fontColor);
    }
    else {
        writeJson(jsonPath);
        QJsonObject json = jsonFile();
        theme = Notepad->themeColor(getJsonValue(json, "Theme"), getJsonValue(json, "TextColor"));
    }

    return theme;
}

QJsonObject json::jsonFile()
{
//    Default json
    QJsonObject jsonObj;

    jsonObj["Theme"] = "Dark";
    jsonObj["TextColor"] = "White";
    jsonObj["Voice"] = "Lady";
    jsonObj["FontSize"] = "11";
    jsonObj["FontColor"] = "White";
    jsonObj["FontFamily"] = "Arial";

    return jsonObj;
}

void json::writeJson(QString jsonPath)
{
    QJsonObject jsonObj = jsonFile();
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);

    QFile file(jsonPath);

//        Write json
    if (!file.open(QFile::WriteOnly)){
        qWarning("not open");
    }
    file.write(jsonDoc.toJson());
    file.close();
}

QJsonObject json::readJson(QString jsonPath)
{
//    Read json file
    QFile file(jsonPath);
    if (!file.open(QFile::ReadOnly)){
        return jsonFile();
    }
    else {
        QJsonParseError jsonParseError;
        QJsonDocument jsonDoc = QJsonDocument().fromJson(file.readAll(), &jsonParseError);
        file.close();

        QJsonObject jsonObj = jsonDoc.object();
        return jsonObj;
    }
}

QJsonObject json::checkAndCreateFolder()
{
    QJsonObject jsonObj;

    QString folderPath = Notepad->path("Folder");
    QString jsonPath = Notepad->path("jsonName");

//    Check exists folder/json and write
    if (!QDir(folderPath).exists()){
        QDir().mkdir(folderPath);

        writeJson(jsonPath);
    }
    else {
        if (!QFile().exists(jsonPath)){
            writeJson(jsonPath);
            jsonObj =  jsonFile();
        }
        else {
            jsonObj = readJson(jsonPath);
        }
    }

    return jsonObj;
}

void json::dataWriteOnJson(QString key, QString value)
{
//    Read json file
    QString jsonPath = Notepad->path("jsonName");
    QFile file(jsonPath);

    if (file.open(QFile::ReadOnly)){
        QJsonParseError jsonParseError;
        QJsonDocument jsonDoc = QJsonDocument().fromJson(file.readAll(), &jsonParseError);
        file.close();

        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj.find(key).value().toString() != ""){
            jsonObj[key] = value;

            jsonDoc.setObject(jsonObj);
            QFile file(jsonPath);

//            Write json
            if (file.open(QFile::WriteOnly)){
                file.write(jsonDoc.toJson());
                file.close();
            }
        }
    }
}
