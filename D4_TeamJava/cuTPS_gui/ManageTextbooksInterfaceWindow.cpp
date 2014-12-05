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

//List getters
QAbstractItemView* ManageTextbooksInterfaceWindow::getTextbooksListView()   { return ui->textbooksListView; }
QAbstractItemView* ManageTextbooksInterfaceWindow::getChaptersListView()    { return ui->chaptersListView; }
QAbstractItemView* ManageTextbooksInterfaceWindow::getSectionsListView()    { return ui->sectionsListView; }

//Button getters
QPushButton* ManageTextbooksInterfaceWindow::getBackButton()            { return ui->backButton; }
QPushButton* ManageTextbooksInterfaceWindow::getEditTextbookButton()    { return ui->editTextbookOption; }
QPushButton* ManageTextbooksInterfaceWindow::getModifyTextbookButton()  { return ui->modifyTextbookOption; }
QPushButton* ManageTextbooksInterfaceWindow::getDeleteTextbookButton()  { return ui->deleteTextbookOption; }
