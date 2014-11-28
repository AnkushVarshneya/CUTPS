#include "createchapterformwindow.h"
#include "ui_createchapterformwindow.h"

CreateChapterFormWindow::CreateChapterFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateChapterFormWindow)
{
    ui->setupUi(this);
}

CreateChapterFormWindow::~CreateChapterFormWindow()
{
    delete ui;
}
