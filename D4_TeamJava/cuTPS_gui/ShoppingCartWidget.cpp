#include "ShoppingCartWidget.h"
#include "ui_ShoppingCartWidget.h"

ShoppingCartWidget::ShoppingCartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingCartWidget)
{
    ui->setupUi(this);
}

ShoppingCartWidget* ShoppingCartWidget::instance = 0;

//singleton instance getter
ShoppingCartWidget* ShoppingCartWidget::getInstance()
{
    if (instance == 0){
    instance = new ShoppingCartWidget();
    }
return instance;
}

//getters
QPushButton* ShoppingCartWidget::getCloseOption() { return ui->closeOption; }
QPushButton* ShoppingCartWidget::getCheckoutOption() { return ui->checkoutOption; }
QPushButton* ShoppingCartWidget::getEmptyCartOption() { return ui->emptyCartOption; }

//setters
void ShoppingCartWidget::setCartViewModel(QStandardItemModel *mod)
{
    if(mod != NULL) { ui->cartListView->setModel(mod) ; }
}

void ShoppingCartWidget::setOrderTotalText(QString text)
{
    ui->orderTotalDisplay->setText(text);
}

ShoppingCartWidget::~ShoppingCartWidget()
{
    delete ui;
}
