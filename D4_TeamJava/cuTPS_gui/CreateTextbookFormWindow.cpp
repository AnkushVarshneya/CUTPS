#include "CreateTextbookFormWindow.h"
#include "ui_CreateTextbookFormWindow.h"

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

void CreateTextbookFormWindow::on_viewEditChaptersButton_clicked()
{
    createChapterForm.show();
    this->hide();
}
