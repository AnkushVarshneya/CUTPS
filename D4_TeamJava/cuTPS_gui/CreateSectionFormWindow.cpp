#include "CreateSectionFormWindow.h"
#include "ui_CreateSectionFormWindow.h"

#include "CreateChapterFormWindow.h"

CreateSectionFormWindow::CreateSectionFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateSectionFormWindow)
{
    ui->setupUi(this);
}

CreateSectionFormWindow::~CreateSectionFormWindow()
{
    delete ui;
}

void CreateSectionFormWindow::on_backButton_clicked()
{
    parentWindow->show();
    this->hide();
}
