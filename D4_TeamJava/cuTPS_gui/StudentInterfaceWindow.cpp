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


//    OurStandardItem *treeItem = new OurStandardItem(treeText);
//    treeMod = new QStandardItemModel(this);
//    treeMod->appendRow(treeItem);
//    ui->itemsTreeView->setModel(treeMod);

}

StudentInterfaceWindow::~StudentInterfaceWindow()
{
    delete ui;
}

//getters
QPushButton*    StudentInterfaceWindow::getAddTextbookOption() { return ui->addTextbookToCartOption; }
QPushButton*    StudentInterfaceWindow::getViewDetailsOption() {return ui->viewDetailsOption; }
QPushButton*    StudentInterfaceWindow::getViewCartOption() { return ui->viewShoppingCartOption; }
QComboBox*      StudentInterfaceWindow::getTermSelectOption() { return ui->termSelectOption;  }
QSpinBox*       StudentInterfaceWindow::getQuantityOption() { return ui->quantityOption; }
QAbstractItemView* StudentInterfaceWindow::getCourseTreeView() { return ui->itemsTreeView; }

void StudentInterfaceWindow::on_viewDetailsOption_clicked()
{
    qDebug() << "not implemented here anymore as interface itself doesnt have the mode;";
   // qDebug() << treeMod->itemFromIndex(ui->itemsTreeView->currentIndex())->data();

}
