#ifndef CHECKOUTDIALOGWIDGET_H
#define CHECKOUTDIALOGWIDGET_H

#include <QDialog>

namespace Ui {
class CheckoutDialogWidget;
}

class CheckoutDialogWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CheckoutDialogWidget(QWidget *parent = 0);
    ~CheckoutDialogWidget();

private:
    Ui::CheckoutDialogWidget *ui;
};

#endif // CHECKOUTDIALOGWIDGET_H
