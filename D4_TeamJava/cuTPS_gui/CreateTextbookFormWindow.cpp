#include "createtextbookformwindow.h"
#include "ui_createtextbookformwindow.h"

CreateTextbookFormWindow::CreateTextbookFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTextbookFormWindow)
{
    ui->setupUi(this);
}

CreateTextbookFormWindow::~CreateTextbookFormWindow()
{
    delete ui;
}

void CreateTextbookFormWindow::on_backButton_clicked()
{

}

void CreateTextbookFormWindow::on_ViewEditChaptersButton_clicked()
{

}
