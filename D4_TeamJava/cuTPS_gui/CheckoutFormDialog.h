#ifndef CHECKOUTFORMDIALOG_H
#define CHECKOUTFORMDIALOG_H

#include <QDialog>

namespace Ui {
class CheckoutFormDialog;
}

class CheckoutFormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckoutFormDialog(QWidget *parent = 0);
    ~CheckoutFormDialog();

private:
    Ui::CheckoutFormDialog *ui;
};

#endif // CHECKOUTFORMDIALOG_H
