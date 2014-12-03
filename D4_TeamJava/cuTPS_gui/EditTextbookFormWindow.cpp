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
    return ui->editChapterButton;
}

QPushButton *EditTextbookFormWindow::getCreateButton()
{
    return ui->createButton;
}

QPushButton *EditTextbookFormWindow::getAddChapterButton()
{
    return ui->createChapterButton;
}
