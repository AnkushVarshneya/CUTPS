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

QPushButton* EditChapterFormWindow::getBackButton()
{
    return ui->backButton;
}

QPushButton* EditChapterFormWindow::getCreateButton()
{
    return ui->createButton;
}

QPushButton* EditChapterFormWindow::getEditSectionButton()
{
    return ui->viewEditSectionButton;
}

QPushButton* EditChapterFormWindow::getCreateSectionButton()
{
    return ui->createSectionButton;
}
