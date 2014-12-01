#include "CreateTextbookFormWindow.h"
#include "ui_CreateTextbookFormWindow.h"

#include "ManageTextbooksInterfaceWindow.h"

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
    createChapterForm.parentWindow = this;
    this->hide();
}

void CreateTextbookFormWindow::on_backButton_clicked()
{
    parentWindow->show();
    this->hide();
}

void CreateTextbookFormWindow::on_createButton_clicked()
{
    Textbook *t = new Textbook(ui->titleTextbox->text(),    ui->authorTextbox->text(),      ui->editionTextbox->text(),
                               ui->publisherTextbox->text(),ui->isbnTextbox->text(),        ui->descriptionTextbox->toPlainText(),
                               0,                   ui->priceSpinBox->value(),       ui->availabilityCheckBox->isChecked());


}
