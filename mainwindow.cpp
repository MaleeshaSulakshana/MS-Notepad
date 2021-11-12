#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

//    Check and create folder
    jsonObj =  classJson->checkAndCreateFolder();

    ui->selectTheme->setCurrentText(jsonObj["Theme"].toString());
    ui->selectThemeFontColor->setCurrentText(jsonObj["TextColor"].toString());
    ui->selectVoice->setCurrentText(jsonObj["Voice"].toString());

    QString theme = classJson->themeSelect(jsonObj);
    MainWindow::setStyleSheet(theme);

//    Set Default values
    speaker = new QTextToSpeech();
    voices = speaker->availableVoices();
    speaker->setVoice(voices.at((ui->selectVoice->currentIndex())));
    speaker->setVolume(100);

//    Set btnPanel index
    ui->btnPanel->setCurrentIndex(0);

//    Set test edit font wheight normal
    ui->textEdit->setFontWeight(QFont::Normal);

//    Add available fonts to font combo box
    QStringList fontFamilies;
    if(fontFamilies.isEmpty())
            fontFamilies = QFontDatabase().families();

    for (int i = 0; i < fontFamilies.count() ; i++ ) {
        ui->fontList->addItem(fontFamilies[i]);
    }

//    Add standed font sizes to list
    QList<int> fontSizes;
    if(fontSizes.isEmpty())
        fontSizes = QFontDatabase().standardSizes();

    for (int i = 0; i < fontSizes.count() ; i++ ) {
        QString fontsize = QString::number(fontSizes[i]);
        ui->fontSizeList->addItem(fontsize);
    }

//    Set font and point settings
    setText();

//    Set forcus cursor in text-edit
    ui->textEdit->setFocus();

//    Set disable true
    ui->btnResume->setDisabled(true);
    ui->btnPaused->setDisabled(true);
    ui->btnStop->setDisabled(true);

}

void MainWindow::setText()
{
    QString fontsize = jsonObj.find("FontSize").value().toString();
    QString fontfamily = jsonObj.find("FontFamily").value().toString();
    QString fontcolor = jsonObj.find("FontColor").value().toString();

//    Set font settings
    ui->textEdit->setFontPointSize(fontsize.toInt());
    ui->textEdit->setFontFamily(fontfamily);
    ui->textEdit->setTextColor(fontcolor);

//    Set font setting lists current text
    ui->fontList->setCurrentText(fontfamily);
    ui->fontSizeList->setCurrentText(fontsize);
    ui->fontColor->setCurrentText(fontcolor);

//    Set focus
    ui->textEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::changeBgColorDeactive(QString name)
{
    QString deactivecolor = ""+name+" {background: "+ jsonObj.find("Theme").value().toString() +"; "
                                        "border-color: "+ jsonObj.find("Theme").value().toString() +";}";
    return deactivecolor;
}

QString MainWindow::changeBgColorActive(QString name)
{
    QString activecolor = ""+name+" {background: #c1c1c1; border-color: #c1c1c1;}";
    return activecolor;
}

void MainWindow::on_btnNew_clicked()
{
//    Create new text file
    file_path = "";
    ui->textEdit->clear();
    setText();
}

void MainWindow::on_btnOpen_clicked()
{
//    Open local file
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file!");
    QFile file(file_name);

    file_path = file_name;

    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning..","File not open!");
        return;
    }

    QTextStream inputfile(&file);
    QString text = inputfile.readAll();
    ui->textEdit->setText(text);

    file.close();
}

void MainWindow::on_btnSave_clicked()
{
//    Save latest edits to relevent file
    if (ui->textEdit->toPlainText() == ""){
        QMessageBox::warning(this,"Warning..","No data to save!");
    }
    else{

        if (file_path == "") {
            file_path = QFileDialog::getSaveFileName(this,
                                                     tr("Open the file"), "*.txt",
                                                     tr("Save file (*.txt);;All Files"));
        }

        QFile file(file_path);

        if (!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "Warning..","File not save!");
            return;
        }

        QTextStream outputfile(&file);
        QString text = ui->textEdit->toPlainText();
        outputfile << text;
        file.flush();

        file.close();
    }
}

void MainWindow::on_btnSaveAs_clicked()
{
//    Save latest edits to choosing new file
    if (ui->textEdit->toPlainText() == ""){
        QMessageBox::warning(this,"Waring","No data to save!");
    }
    else{

        QString file_name = QFileDialog::getSaveFileName(this,
                                                         tr("Open the file"), "*.txt",
                                                         tr("Save file (*.txt);;All Files"));
        QFile file(file_name);

        file_path = file_name;

        if (!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this, "Waring..","File not save!");
            return;
        }

        QTextStream outputfile(&file);
        QString text = ui->textEdit->toPlainText();
        outputfile << text;
        file.flush();

        file.close();
    }
}

void MainWindow::on_btnCopy_clicked()
{
    ui->textEdit->copy();
    setText();
}

void MainWindow::on_btnCut_clicked()
{
    ui->textEdit->cut();
    setText();
}

void MainWindow::on_btnPaste_clicked()
{
    ui->textEdit->paste();
    setText();
}

void MainWindow::on_btnUndo_clicked()
{
    ui->textEdit->undo();
    setText();
}

void MainWindow::on_btnRedo_clicked()
{
    ui->textEdit->redo();
    setText();
}

void MainWindow::on_textEdit_textChanged()
{
//    Display word count in text edit
    int wordCount = ui->textEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+")
                                                      , QString::SkipEmptyParts).count();

    QString wcount = QString::number(wordCount);
    ui->lblWordCount->setText("Word Count : " + wcount);
}

void MainWindow::on_btnText_clicked()
{
    if (ui->btnPanel->currentIndex() == 1){
        ui->btnPanel->setCurrentIndex(0);
    }
    else {
        ui->btnPanel->setCurrentIndex(1);
    }
}

void MainWindow::on_btnSpeaker_clicked()
{
    if (ui->btnPanel->currentIndex() == 2){
        ui->btnPanel->setCurrentIndex(0);
    }
    else {
        ui->btnPanel->setCurrentIndex(2);
    }
}

void MainWindow::on_fontList_activated(const QString &selectedFontFamily)
{
    ui->textEdit->setFontFamily(selectedFontFamily);
    ui->textEdit->setFocus();
    classJson->dataWriteOnJson("FontFamily", selectedFontFamily);
}

void MainWindow::on_fontSizeList_activated(const QString &selectedFontSize)
{
    ui->textEdit->setFontPointSize(selectedFontSize.toInt());
    ui->textEdit->setFocus();
    classJson->dataWriteOnJson("FontSize", selectedFontSize);
}

void MainWindow::on_btnBold_clicked()
{
    QTextCursor txtCursor = ui->textEdit->textCursor();
    if (!txtCursor.charFormat().font().bold()){
        ui->textEdit->setFontWeight(QFont::Bold);
        ui->btnBold->setStyleSheet(changeBgColorActive("#btnBold"));
    }
    else{
        ui->textEdit->setFontWeight(QFont::Normal);
        ui->btnBold->setStyleSheet(changeBgColorDeactive("#btnBold"));
    }

    setText();
}

void MainWindow::on_btnItelic_clicked()
{
    QTextCursor txtCursor = ui->textEdit->textCursor();
    if (!txtCursor.charFormat().font().italic()){
        ui->textEdit->setFontItalic(true);
        ui->btnItelic->setStyleSheet(changeBgColorActive("#btnItelic"));
    }
    else {
        ui->textEdit->setFontItalic(false);
        ui->btnItelic->setStyleSheet(changeBgColorDeactive("#btnItelic"));
    }

    setText();
}

void MainWindow::on_btnUnderline_clicked()
{
    QTextCursor txtCursor = ui->textEdit->textCursor();
    if (!txtCursor.charFormat().font().underline()){
        ui->textEdit->setFontUnderline(true);
        ui->btnUnderline->setStyleSheet(changeBgColorActive("#btnUnderline"));
    }
    else {
        ui->textEdit->setFontUnderline(false);
        ui->btnUnderline->setStyleSheet(changeBgColorDeactive("#btnUnderline"));
    }

    setText();
}

void MainWindow::on_fontColor_activated(const QString &fontColor)
{
    ui->textEdit->setTextColor(fontColor);
    classJson->dataWriteOnJson("FontColor", fontColor);
    ui->textEdit->setFocus();
}

void MainWindow::on_btnPlay_clicked()
{
    speaker->say(ui->textEdit->toPlainText());

//    Set disable
    ui->btnResume->setDisabled(true);
    ui->btnPaused->setDisabled(false);
    ui->btnStop->setDisabled(false);
}

void MainWindow::on_btnPaused_clicked()
{
    QTextToSpeech::State speakerState;
    speakerState = speaker->state();

    if (speakerState == QTextToSpeech::Speaking) {
        speaker->pause();

//    Set disable
        ui->btnPaused->setDisabled(true);
        ui->btnResume->setDisabled(false);
    }
}

void MainWindow::on_btnResume_clicked()
{
    QTextToSpeech::State speakerState;
    speakerState = speaker->state();

    if (speakerState == QTextToSpeech::Paused){
        speaker->resume();

//    Set disable
        ui->btnResume->setDisabled(true);
        ui->btnPaused->setDisabled(false);
        ui->btnStop->setDisabled(false);
    }
}

void MainWindow::on_btnStop_clicked()
{
    QTextToSpeech::State speakerState;
    speakerState = speaker->state();

    if (speakerState == QTextToSpeech::Speaking || speakerState == QTextToSpeech::Paused) {
        speaker->stop();

//    Set disable
        ui->btnResume->setDisabled(true);
        ui->btnPaused->setDisabled(true);
        ui->btnStop->setDisabled(true);
    }
}

void MainWindow::on_selectVoice_activated(int voiceNumber)
{
    speaker->setVoice(voices.at(voiceNumber));
    classJson->dataWriteOnJson("Voice", ui->selectVoice->currentText());
}

void MainWindow::on_btnTheme_clicked()
{
    if (ui->btnPanel->currentIndex() == 3){
        ui->btnPanel->setCurrentIndex(0);
    }
    else {
        ui->btnPanel->setCurrentIndex(3);
    }
}

void MainWindow::on_selectTheme_activated(const QString &selectedTheme)
{
    QString theme = classNotepad->themeColor(selectedTheme, ui->selectThemeFontColor->currentText());
    MainWindow::setStyleSheet(theme);
    classJson->dataWriteOnJson("Theme", selectedTheme);
}

void MainWindow::on_selectThemeFontColor_activated(const QString &fontColor)
{
    QString theme = classNotepad->themeColor(ui->selectTheme->currentText(), fontColor);
    MainWindow::setStyleSheet(theme);

    ui->textEdit->setTextColor(fontColor);
    ui->fontColor->setCurrentText(fontColor);

    classJson->dataWriteOnJson("TextColor", fontColor);
    classJson->dataWriteOnJson("FontColor", fontColor);
}

void MainWindow::on_btnInfo_clicked()
{
    QMessageBox::information(this, "Information", "Shortcut Keys For Easily Use \n\n"
                              "\t- New File -> Ctrl + N \n"
                              "\t- Open -> Ctrl + O \n"
                              "\t- Save -> Ctrl + S \n"
                              "\t- Save As -> Ctrl + Shift + S \n"
                              "\t- Copy -> Ctrl + C \n"
                              "\t- Cut -> Ctrl + X \n"
                              "\t- Paste -> Ctrl + V \n"
                              "\t- Undo -> Ctrl + Z \n"
                              "\t- Redo -> Ctrl + Y \n"
                              "\t- Text -> Ctrl + T \n"
                              "\t- Bold -> Ctrl + B \n"
                              "\t- Underline -> Ctrl + U \n"
                              "\t- Italic -> Ctrl + I \n"
                              "\t- Speaker -> Alt + S \n"
                              "\t- Play -> Ctrl + A \n"
                              "\t- Pause -> Ctrl + P \n"
                              "\t- Reseume -> Ctrl + R \n"
                              "\t- Stop -> Shift + S \n"
                              "\t- Theme -> Alt + T \n"
                              "\t- Information -> Alt + I \n"
                              "\nDeveloped By - M P M S Jayasinghe"
                              "\nVersion - v1.0");
}
