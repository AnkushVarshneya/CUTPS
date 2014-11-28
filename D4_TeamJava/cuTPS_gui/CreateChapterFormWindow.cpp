#include "CreateChapterFormWindow.h"
#include "ui_CreateChapterFormWindow.h"

#include "CreateTextbookFormWindow.h"

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

void CreateChapterFormWindow::on_viewEditSectionButton_clicked()
{
    createSectionForm.show();
    createSectionForm.parentWindow = this;
    this->hide();
}

void CreateChapterFormWindow::on_pushButton_clicked()
{

}
