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

//Button getters
QPushButton* EditSectionFormWindow::getBackButton()     { return ui->backButton; }
QPushButton* EditSectionFormWindow::getCreateButton()   { return ui->createButton; }

//Field getters
QLineEdit*      EditSectionFormWindow::getTitleTextbox()        { return ui->titleTextbox; }
QSpinBox*       EditSectionFormWindow::getSectionNumberSpinBox(){ return ui->sectionNumberSpinBox; }
QDoubleSpinBox* EditSectionFormWindow::getPriceSpinBox()        { return ui->priceSpinBox; }
QCheckBox*      EditSectionFormWindow::getAvailabilityCheckBox(){ return ui->availabilityCheckBox; }
