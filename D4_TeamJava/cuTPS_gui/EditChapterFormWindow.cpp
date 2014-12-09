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

//Button getters
QPushButton* EditChapterFormWindow::getBackButton()             { return ui->backButton; }
QPushButton* EditChapterFormWindow::getCreateButton()           { return ui->createButton; }
QPushButton* EditChapterFormWindow::getEditSectionButton()      { return ui->viewEditSectionButton; }
QPushButton* EditChapterFormWindow::getCreateSectionButton()    { return ui->createSectionButton; }
QPushButton* EditChapterFormWindow::getDeleteSectionButton()    { return ui->deleteSectionButton; }

//Field getters
QLineEdit*      EditChapterFormWindow::getTitleTextbox()        { return ui->titleTextbox; }
QSpinBox*       EditChapterFormWindow::getChapterNumberSpinBox(){ return ui->chapterNumberSpinBox; }
QDoubleSpinBox* EditChapterFormWindow::getPriceSpinBox()        { return ui->priceSpinBox; }
QCheckBox*      EditChapterFormWindow::getAvailabilityCheckBox(){ return ui->availabilityCheckBox; }

//List getter
QListView*      EditChapterFormWindow::getSectionsListView()    { return ui->sectionsList; }
