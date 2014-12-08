#include "LinkTextbookFormWindow.h"
#include "ui_LinkTextbookFormWindow.h"

LinkTextbookFormWindow::LinkTextbookFormWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkTextbookFormWindow)
{
    ui->setupUi(this);
}

LinkTextbookFormWindow::~LinkTextbookFormWindow()
{
    delete ui;
}
