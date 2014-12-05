#include "TextbookDetailsWindow.h"
#include "ui_TextbookDetailsWindow.h"

TextbookDetailsWindow::TextbookDetailsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextbookDetailsWindow)
{
    this->setWindowModality(Qt::WindowModal);
    ui->setupUi(this);
}

TextbookDetailsWindow::TextbookDetailsWindow(Textbook *textbook, QWidget *parent) {


}


TextbookDetailsWindow::~TextbookDetailsWindow()
{
    delete ui;
}
