#include "ConfirmationDialogWindow.h"
#include "ui_ConfirmationDialogWindow.h"

ConfirmationDialogWindow::ConfirmationDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmationDialogWindow)
{
    ui->setupUi(this);
}

ConfirmationDialogWindow::~ConfirmationDialogWindow()
{
    delete ui;
}

QPushButton*    ConfirmationDialogWindow::getYesButton()        { return ui->yesButton; }
QPushButton*    ConfirmationDialogWindow::getNoButton()         { return ui->noButton; }
QTextEdit* ConfirmationDialogWindow::getMessageTextBox()        { return ui->messageTextBox; }
