#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearConsole();
    void updateBackground(string path);
    void addStringToConsole(string input);
    void overwriteConsole(string input);
    void parseInput(string input);
    void scrollToBottom();
    QMovie* currentMovie;

private slots:
    void on_textEdit_textChanged();
    void on_upButton_released();
    void on_downButton_released();
    void on_rightButton_released();
    void on_leftButton_released();
    void on_quitButton_released();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
