#ifndef VOLUME_H
#define VOLUME_H

#include <QString>
#include <QDir>

class notepad
{
public:
    notepad();

    void setVolume(int);

    int getVolume();

    QString path(QString file);

    QString themeColor(QString color, QString fontColor);

private:
    int vol;
}; 

#endif // VOLUME_H
