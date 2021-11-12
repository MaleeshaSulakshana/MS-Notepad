#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Include custom libraries
#include <QTextToSpeech>
#include <QDialogButtonBox>
#include <QLoggingCategory>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDatabase>
#include <QFont>
#include <QIcon>
#include <QStandardPaths>
#include <QDir>
#include <QJsonObject>
#include <QJsonValue>

//Class files
#include "notepad.h"
#include "json.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void setText();

    QString changeBgColorDeactive(QString name);

    QString changeBgColorActive(QString name);

    void on_btnNew_clicked();

    void on_btnOpen_clicked();

    void on_btnSave_clicked();

    void on_btnSaveAs_clicked();

    void on_btnCopy_clicked();

    void on_btnCut_clicked();

    void on_btnPaste_clicked();

    void on_btnUndo_clicked();

    void on_btnRedo_clicked();

    void on_textEdit_textChanged();

    void on_btnText_clicked();

    void on_btnSpeaker_clicked();

    void on_fontList_activated(const QString &arg1);

    void on_fontSizeList_activated(const QString &arg1);

    void on_btnBold_clicked();

    void on_btnItelic_clicked();

    void on_btnUnderline_clicked();

    void on_btnPlay_clicked();

    void on_btnPaused_clicked();

    void on_btnStop_clicked();

    void on_selectVoice_activated(int index);

    void on_fontColor_activated(const QString &arg1);

    void on_btnTheme_clicked();

    void on_selectTheme_activated(const QString &arg1);

    void on_selectThemeFontColor_activated(const QString &arg1);

    void on_btnResume_clicked();


    void on_btnInfo_clicked();

private:
    Ui::MainWindow *ui;

    QString file_path;

    QTextToSpeech *speaker;
    QVector<QVoice> voices;
    QDialogButtonBox* buttonBox;

    notepad* classNotepad;
    json* classJson;
    QJsonObject jsonObj;

};
#endif // MAINWINDOW_H
