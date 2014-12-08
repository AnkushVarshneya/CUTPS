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


ShoppingCartWidget::~ShoppingCartWidget()
{
    delete ui;
}

void ShoppingCartWidget::setCartViewModel(QStandardItemModel *mod)
{
    if(mod != NULL) { ui->cartListView->setModel(mod) ; }
}

