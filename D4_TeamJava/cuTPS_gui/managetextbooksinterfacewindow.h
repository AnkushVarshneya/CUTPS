#ifndef MANAGETEXTBOOKSINTERFACEWINDOW_H
#define MANAGETEXTBOOKSINTERFACEWINDOW_H

#include <QWidget>
#include "createtextbookformwindow.h"

namespace Ui {
class ManageTextbooksInterfaceWindow;
}

class ManageTextbooksInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageTextbooksInterfaceWindow(QWidget *parent = 0);
    ~ManageTextbooksInterfaceWindow();

private slots:
    void on_createTextbookOption_clicked();

private:
    Ui::ManageTextbooksInterfaceWindow *ui;
    CreateTextbookFormWindow createTextbookForm;
};

#endif // MANAGETEXTBOOKSINTERFACEWINDOW_H
