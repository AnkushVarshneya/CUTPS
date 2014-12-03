#include "EditChapterFormWindow.h"
#include "ui_EditChapterFormWindow.h"

#include "EditTextbookFormWindow.h"

EditChapterFormWindow::EditChapterFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditChapterFormWindow)
{
    ui->setupUi(this);
}

EditChapterFormWindow::~EditChapterFormWindow()
{
    delete ui;
}

void EditChapterFormWindow::on_viewEditSectionButton_clicked()
{
    editSectionForm.show();
    editSectionForm.parentWindow = this;
    this->hide();
}

void EditChapterFormWindow::on_pushButton_clicked()
{
    parentWindow->show();
    this->hide();
}
