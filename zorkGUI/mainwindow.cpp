#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "dialogues.h"
#include "command.h"
#include "ZorkUL.h"

#include <QMovie>

using namespace Constants;

// Here we set the basics by setting the icon for the window and all the different properties.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/locations/locations/logo.png"));
    ui->setupUi(this);
    ui->outputConsole->setWordWrap(true);

    ui->background->setScaledContents(true);
    ui->textEdit->setFocus();
}

// Window deconstructor.
MainWindow::~MainWindow()
{
    delete ui;

    // Deleting the current movie.
    if (this->currentMovie != NULL) {
        delete this->currentMovie;
    }
}

// Clearing the console.
void MainWindow::clearConsole() {
    ui->outputConsole->clear();
}

// Printing to game console supports string and QString.
void MainWindow::addStringToConsole(string input) {
    ui->outputConsole->setText(ui->outputConsole->text() + QString::fromStdString("\n") + QString::fromStdString(input));
}

// Clears the console and prints the input given.
void MainWindow::overwriteConsole(string input) {
    ui->outputConsole->clear();
    addStringToConsole(input);
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

// Handling what happens when the "enter" key is pressed on the text edit input.
void MainWindow::on_textEdit_textChanged() {
    // Converting the input from user from QString to string and finding index of "\n".
    string input = ui->textEdit->toPlainText().toStdString();
    size_t newLineIndex = input.find('\n');

    // Preventing users from pressing enter several times.
    if (newLineIndex == 0) {
        ui->textEdit->clear();
        return;
    }

    // Removing the "\n" from the string.
    input = input.substr(0, newLineIndex);

    // Checks if there are any newlines or if the "enter" key is pressed.
    if(newLineIndex != string::npos && input.size() > 0){
        this->parseInput(input);

        ui->textEdit->clear();
    }
}

// Trying to convert input to a command and printing out the appropriate output.
void MainWindow::parseInput(string input){
    Command *command = ZorkUL::getParser()->convertToCommand(input);
    string output = ZorkUL::processCommand(*command, this);

    // Processes errors available.
    if(output.compare("") == 0){
        if(ZorkUL::getCurrentRoom()->getRoomType() == Room::WORDLE) {
            overwriteConsole("You can not leave this room until you complete the world, your only option is to quit.");
            return;
        }
        overwriteConsole(Dialogues::inputError);
        return;
    }

    overwriteConsole(output);
    delete command;

    ui->textEdit->setFocus();
}

// Button releasing for all buttons.
void MainWindow::on_upButton_released() {
    parseInput("go north");
}

void MainWindow::on_rightButton_released() {
    parseInput("go east");
}

void MainWindow::on_downButton_released() {
    parseInput("go south");
}

void MainWindow::on_leftButton_released() {
    parseInput("go west");
}

void MainWindow::on_quitButton_released() {
    parseInput("quit");
}

void MainWindow::on_mapButton_released() {
    parseInput("map");
}

void MainWindow::on_interactButton_released() {
    parseInput("interact");
}
