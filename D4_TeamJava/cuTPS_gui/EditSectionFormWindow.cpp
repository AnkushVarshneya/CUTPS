#include "EditSectionFormWindow.h"
#include "ui_EditSectionFormWindow.h"

#include "EditChapterFormWindow.h"

EditSectionFormWindow::EditSectionFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditSectionFormWindow)
{
    ui->setupUi(this);
}

EditSectionFormWindow::~EditSectionFormWindow()
{
    delete ui;
}

void EditSectionFormWindow::on_backButton_clicked()
{
    parentWindow->show();
    this->hide();
}
