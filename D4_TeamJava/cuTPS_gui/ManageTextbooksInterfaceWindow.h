#ifndef MANAGETEXTBOOKSINTERFACEWINDOW_H
#define MANAGETEXTBOOKSINTERFACEWINDOW_H

#include <QWidget>
#include "EditTextbookFormWindow.h"
#include <QPushButton>

class ContentManagerInterfaceWindow;

namespace Ui {
class ManageTextbooksInterfaceWindow;
}

class ManageTextbooksInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageTextbooksInterfaceWindow(QWidget *parent = 0);
    ~ManageTextbooksInterfaceWindow();

    ContentManagerInterfaceWindow *parentWindow;

    QPushButton* getBackButton();
    QPushButton* getEditTextbookButton();
    QPushButton* getModifyTextbookButton();
    QPushButton* getDeleteTextbookButton();


/*
private slots:
    void on_editTextbookOption_clicked();

    void on_deleteTextbookOption_clicked();

    void on_backButton_clicked();
*/
private:
    Ui::ManageTextbooksInterfaceWindow *ui;
    EditTextbookFormWindow editTextbookForm;
};

#endif // MANAGETEXTBOOKSINTERFACEWINDOW_H
