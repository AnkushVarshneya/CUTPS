#include "StudentShopView.h"
#include "ui_StudentShopView.h"

StudentShopView::StudentShopView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentShopView)
{
    ui->setupUi(this);
    //Setting the icon's image to a Shopping Cart
//    QPixmap shopping_img("../Images/shopping_cart_clipart.png");
//    QIcon ButtonIcon(shopping_img);

//    ui->viewShoppingCartOption->setIcon(ButtonIcon);
//    ui->viewShoppingCartOption->setIconSize(shopping_img.rect().size());
//    ui->viewShoppingCartOption->setFixedSize(shopping_img.rect().size());
}

StudentShopView::~StudentShopView()
{
    delete ui;
}

QPushButton*    StudentShopView::getAddTextbookOption() { return ui->addTextbookToCartOption; }
QPushButton*    StudentShopView::getViewDetailsOption() {return ui->viewDetailsOption; }
QPushButton*    StudentShopView::getViewCartOption() { return ui->viewShoppingCartOption; }
QComboBox*      StudentShopView::getTermSelectOption() { return ui->termSelectOption;  }
QSpinBox*       StudentShopView::getQuantityOption() { return ui->quantityOption; }
QListView*      StudentShopView::getCourseView() {return ui->itemsListView; }

