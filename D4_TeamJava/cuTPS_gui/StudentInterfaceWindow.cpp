#include "StudentInterfaceWindow.h"
#include "ui_StudentInterfaceWindow.h"

#include <QPixmap>
#include <QIcon>

StudentInterfaceWindow::StudentInterfaceWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentInterfaceWindow)
{
    ui->setupUi(this);

    //Setting the icon's image to a Shopping Cart
    QPixmap shopping_img("../Images/shopping_cart_clipart.png");
    QIcon ButtonIcon(shopping_img);
    ui->viewShoppingCartOption->setIcon(ButtonIcon);
    ui->viewShoppingCartOption->setIconSize(shopping_img.rect().size());
    ui->viewShoppingCartOption->setFixedSize(shopping_img.rect().size());
}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}
