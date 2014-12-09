#ifndef SHOPPINGCARTWIDGET_H
#define SHOPPINGCARTWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QPushButton>

namespace Ui {
class ShoppingCartWidget;
}

class ShoppingCartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCartWidget(QWidget *parent = 0);
    static ShoppingCartWidget*      getInstance(); //singleton pattern
    ~ShoppingCartWidget();
    QPushButton*                    getCloseOption();
    QPushButton*                    getCheckoutOption();
    QPushButton*                    getEmptyCartOption();
    void                            setOrderTotalText(QString);
    void                            setCartViewModel(QStandardItemModel *mod);

private:
    Ui::ShoppingCartWidget *ui;
    static ShoppingCartWidget*      instance;

};

#endif // SHOPPINGCARTWIDGET_H
