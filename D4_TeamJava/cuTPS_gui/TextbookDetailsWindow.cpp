#include "TextbookDetailsWindow.h"
#include "ui_TextbookDetailsWindow.h"

TextbookDetailsWindow::TextbookDetailsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextbookDetailsWindow)
{
    ui->setupUi(this);
}

TextbookDetailsWindow::~TextbookDetailsWindow()
{
    delete ui;
}
