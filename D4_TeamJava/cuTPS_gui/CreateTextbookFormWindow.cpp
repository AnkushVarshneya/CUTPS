#include "CreateTextbookFormWindow.h"
#include "ui_CreateTextbookFormWindow.h"

#include "ManageTextbooksInterfaceWindow.h"
#include <QDebug>


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
/*
void CreateTextbookFormWindow::on_viewEditChaptersButton_clicked()
{
    createChapterForm.show();
    createChapterForm.parentWindow = this;
    this->hide();
}


void CreateTextbookFormWindow::on_createButton_clicked()
{
    Textbook *t = new Textbook(ui->titleTextbox->text(),    ui->authorTextbox->text(),      ui->editionTextbox->text(),
                               ui->publisherTextbox->text(),ui->isbnTextbox->text(),        ui->descriptionTextbox->toPlainText(),
                               0,                   ui->priceSpinBox->value(),       ui->availabilityCheckBox->isChecked());

    qDebug() << "i fucked up";
}
*/
Ui::CreateTextbookFormWindow* CreateTextbookFormWindow::getUI()
{
    return ui;
}

QPushButton *CreateTextbookFormWindow::getBackButton()
{
    return ui->backButton;
}

QPushButton *CreateTextbookFormWindow::getViewEditChaptersButton()
{
    return ui->viewEditChaptersButton;
}

QPushButton *CreateTextbookFormWindow::getCreateButton()
{
    return ui->createButton;
}

QPushButton *CreateTextbookFormWindow::getAddChapterButton()
{
    return ui->createChapterButton;
}
