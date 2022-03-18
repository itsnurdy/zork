#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->background->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->currentMovie;
}

// Method used to update the background of the program.
void MainWindow::updateBackground(string path) {

    // Returns npos if a "." is not found.
    if(path.find(".") == string::npos) {
        return;
    }

    // Returns the index of the dot extension.
    int dotIndex = (int) path.find(".");

    // Returns the dot and file type so that we can compare with acceptable ones.
    string fileType = path.substr(dotIndex, (path.length() - dotIndex));

    QString file(QString::fromStdString(path));

    if(fileType.compare(".gif") == 0) {
        this->currentMovie = new QMovie(file);
        ui->background->setScaledContents(true);
        ui->background->setMovie(this->currentMovie);
        this->currentMovie->start();
    }

    else if(fileType.compare(".jpg") == 0 || fileType.compare(".png") == 0){
        QPixmap pixmap(file);
        ui->background->setPixmap(pixmap);
    }
}
