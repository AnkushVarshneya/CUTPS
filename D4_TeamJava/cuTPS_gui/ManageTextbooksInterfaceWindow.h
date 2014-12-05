#ifndef MANAGETEXTBOOKSINTERFACEWINDOW_H
#define MANAGETEXTBOOKSINTERFACEWINDOW_H

#include <QWidget>
#include "EditTextbookFormWindow.h"
#include <QPushButton>

#include "OurStandardItem.h"
#include <QStandardItemModel>


#include <QComboBox>

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

    QAbstractItemView* getTextbooksListView();
    QAbstractItemView* getChaptersListView();
    QAbstractItemView* getSectionsListView();

private:
    Ui::ManageTextbooksInterfaceWindow *ui;
    EditTextbookFormWindow editTextbookForm;
};

#endif // MANAGETEXTBOOKSINTERFACEWINDOW_H
