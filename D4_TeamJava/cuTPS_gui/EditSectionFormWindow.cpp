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

QPushButton* EditSectionFormWindow::getBackButton()     { return ui->backButton; }
QPushButton* EditSectionFormWindow::getCreateButton()   { return ui->createButton; }
