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

EditTextbookFormWindow::~EditTextbookFormWindow()           { delete ui; }
Ui::EditTextbookFormWindow* EditTextbookFormWindow::getUI() { return ui; }

//Button getters
QPushButton* EditTextbookFormWindow::getBackButton()                { return ui->backButton; }
QPushButton* EditTextbookFormWindow::getViewEditChaptersButton()    { return ui->editChapterButton; }
QPushButton* EditTextbookFormWindow::getCreateButton()              { return ui->createButton; }
QPushButton* EditTextbookFormWindow::getAddChapterButton()          { return ui->createChapterButton; }

//Field getters
QLineEdit*      EditTextbookFormWindow::getTitleTextbox()           { return ui->titleTextbox; }
QLineEdit*      EditTextbookFormWindow::getAuthorTextbox()          { return ui->authorTextbox; }
QLineEdit*      EditTextbookFormWindow::getEditionTextbox()         { return ui->editionTextbox; }
QLineEdit*      EditTextbookFormWindow::getPublisherTextbox()       { return ui->publisherTextbox; }
QLineEdit*      EditTextbookFormWindow::getISBNTextbox()            { return ui->isbnTextbox; }
QLineEdit*      EditTextbookFormWindow::getCoverImageTextbox()      { return ui->coverImageTextbox; }
QDoubleSpinBox* EditTextbookFormWindow::getPriceSpinBox()           { return ui->priceSpinBox; }
QCheckBox*      EditTextbookFormWindow::getAvailabilityCheckBox()   { return ui->availabilityCheckBox; }
QTextEdit*      EditTextbookFormWindow::getDescriptionTextbox()     { return ui->descriptionTextbox; }

//List getter
QListView*      EditTextbookFormWindow::getChaptersListView()       { return ui->chaptersList; }
