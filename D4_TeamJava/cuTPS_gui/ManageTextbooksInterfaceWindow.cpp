#include "ManageTextbooksInterfaceWindow.h"
#include "ui_ManageTextbooksInterfaceWindow.h"

#include "ContentManagerInterfaceWindow.h"

ManageTextbooksInterfaceWindow::ManageTextbooksInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageTextbooksInterfaceWindow)
{
    ui->setupUi(this);
}

ManageTextbooksInterfaceWindow::~ManageTextbooksInterfaceWindow()
{
    delete ui;
}


//Button getters
QPushButton* ManageTextbooksInterfaceWindow::getBackButton()
{
    return ui->backButton;
}

QPushButton* ManageTextbooksInterfaceWindow::getEditTextbookButton()
{
    return ui->editTextbookOption;
}

QPushButton* ManageTextbooksInterfaceWindow::getModifyTextbookButton()
{
    return ui->modifyTextbookOption;
}

QPushButton* ManageTextbooksInterfaceWindow::getDeleteTextbookButton()
{
    return ui->deleteTextbookOption;
}
