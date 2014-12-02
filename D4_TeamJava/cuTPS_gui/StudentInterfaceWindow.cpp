#include "StudentInterfaceWindow.h"
#include "ui_StudentInterfaceWindow.h"
#include <QDebug>

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

    //make textbooks for testing
    Textbook    *text1 = new Textbook();
    QListWidgetItem *listItem = new QListWidgetItem(text1->getItemTitle());
    listItem->setData(0, text1->getItemID());
    listItem->setText(text1->getItemTitle());
    ui->textbookListWidget->addItem(listItem);

    qDebug() << ui->textbookListWidget->item(0)->data(0);

    //todo: dummy textbook list
    //rep as standard items: text is some toString, data is itemID
    //treeview for chapters and sections???????????

}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}
