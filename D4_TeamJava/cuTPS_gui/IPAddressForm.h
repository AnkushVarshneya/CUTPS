#ifndef IPADDRESSFORM_H
#define IPADDRESSFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class IPAddressForm;
}

class IPAddressForm : public QWidget
{
    Q_OBJECT

public:
    explicit IPAddressForm(QWidget *parent = 0);
    ~IPAddressForm();

    QLineEdit*      getIPAddressTextBox();
    QPushButton*    getOkButton();

private:
    Ui::IPAddressForm *ui;
};

#endif // IPADDRESSFORM_H
