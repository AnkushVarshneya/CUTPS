#ifndef CHECKOUTFORMDIALOG_H
#define CHECKOUTFORMDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>

namespace Ui {
class CheckoutFormDialog;
}

class CheckoutFormDialog : public QDialog
{
    Q_OBJECT

public:
    static CheckoutFormDialog*   getInstance(); //singleton pattern
    ~CheckoutFormDialog();

    QPushButton*                 getBackOption();
    QPushButton*                 getConfirmOption();
    QLineEdit*                   getNameLineEdit();
    QLineEdit*                   getUnitNumberLineEdit();
    QLineEdit*                   getStreetNameLineEdit();
    QLineEdit*                   getCityLineEdit();
    QLineEdit*                   getPostalCodeLineEdit();
    QLineEdit*                   getProvinceLineEdit();

    QLineEdit*                   getCreditCardNumberLineEdit();
    QLineEdit*                   getCvvLineEdit();
    QLineEdit*                   getCardholderNameLineEdit();
    QLineEdit*                   getExpMonthLineEdit();
    QLineEdit*                   getExpYearLineEdit();

    QComboBox*                   getCardTypeEdit();

protected:
    explicit CheckoutFormDialog(QWidget *parent = 0);

private:
    Ui::CheckoutFormDialog          *ui;
    static CheckoutFormDialog*       instance;

};

#endif // CHECKOUTFORMDIALOG_H
