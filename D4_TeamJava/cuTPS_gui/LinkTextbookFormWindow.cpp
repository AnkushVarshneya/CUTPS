#include "LinkTextbookFormWindow.h"
#include "ui_LinkTextbookFormWindow.h"

LinkTextbookFormWindow::LinkTextbookFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkTextbookFormWindow)
{
    ui->setupUi(this);
}

LinkTextbookFormWindow::~LinkTextbookFormWindow()
{
    delete ui;
}

QPushButton*    LinkTextbookFormWindow::getBackButton()                 { return ui->backButton; }
QPushButton*    LinkTextbookFormWindow::getLinkTextbookButton()         { return ui->linkTextbook; }

QListView*      LinkTextbookFormWindow::getAllTextbooksListView()       { return ui->allTextbooksListView; }
QListView*      LinkTextbookFormWindow::getRegisteredTextbooksListView(){ return ui->registeredTextbooksListView; }
