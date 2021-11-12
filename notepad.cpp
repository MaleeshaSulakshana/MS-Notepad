#include "notepad.h"

notepad::notepad()
{
    vol = 0;
}

void notepad::setVolume(int volume)
{
    vol = volume;
}

int notepad::getVolume()
{
    return vol;
}

QString notepad::path(QString file)
{
//    Create paths
    QString name;
    QString folderPath = QDir::homePath() + "/MS-Notepad";
    QString jsonName = folderPath + "/Theme.json";

    if (file == "Folder"){
        name = folderPath;
    }
    else if (file == "jsonName"){
        name = jsonName;
    }

    return name;
}

QString notepad::themeColor(QString color, QString fontColor)
{
    QString theme;
    if (color == "Dark"){
        theme = "* { background: #222431; color: " + fontColor + ";} "
                            "QPushButton {border: 1px solid " + fontColor + "; border-radius: 10px;} "
                                "QComboBox { background-color: #222431;} QPalette { background: #222431;} "
                                    "#textEdit { border: 1px solid #d1d1d1;}";
    }
    else if (color == "Light") {
        theme = "* { background: #f2f2f2; color: " + fontColor + ";} "
                            "QPushButton {border: 1px solid " + fontColor + "; border-radius: 10px;} "
                                "QComboBox { background-color: #f2f2f2;} QPalette { background: #f2f2f2;} "
                                    "#textEdit { border: 1px solid #222431;}";
    }

    return theme;
}
