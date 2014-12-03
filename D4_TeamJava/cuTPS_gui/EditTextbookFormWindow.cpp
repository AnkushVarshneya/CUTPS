#include "EditTextbookFormWindow.h"
#include "ui_EditTextbookFormWindow.h"

#include "ManageTextbooksInterfaceWindow.h"
#include <QDebug>


EditTextbookFormWindow::EditTextbookFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditTextbookFormWindow)
{
    ui->setupUi(this);
}

EditTextbookFormWindow::~EditTextbookFormWindow()
{
    delete ui;
}
/*
void EditTextbookFormWindow::on_viewEditChaptersButton_clicked()
{
    editChapterForm.show();
    editChapterForm.parentWindow = this;
    this->hide();
}


void EditTextbookFormWindow::on_createButton_clicked()
{
    Textbook *t = new Textbook(ui->titleTextbox->text(),    ui->authorTextbox->text(),      ui->editionTextbox->text(),
                               ui->publisherTextbox->text(),ui->isbnTextbox->text(),        ui->descriptionTextbox->toPlainText(),
                               0,                   ui->priceSpinBox->value(),       ui->availabilityCheckBox->isChecked());

    qDebug() << "i fucked up";
}
*/
Ui::EditTextbookFormWindow* EditTextbookFormWindow::getUI()
{
    return ui;
}

QPushButton *EditTextbookFormWindow::getBackButton()
{
    return ui->backButton;
}

QPushButton *EditTextbookFormWindow::getViewEditChaptersButton()
{
    return ui->viewEditChaptersButton;
}

QPushButton *EditTextbookFormWindow::getCreateButton()
{
    return ui->createButton;
}

QPushButton *EditTextbookFormWindow::getAddChapterButton()
{
    return ui->editChapterButton;
}
