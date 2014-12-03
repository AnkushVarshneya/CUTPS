#ifndef CONTENTMANAGERINTERFACEWINDOW_H
#define CONTENTMANAGERINTERFACEWINDOW_H

#include <QWidget>
#include "ContentInputOutputManager.h"

/*
#include "ManageTextbooksInterfaceWindow.h"
#include "EditTextbookFormWindow.h"
*/

#include <QPushButton>

namespace Ui {
class ContentManagerInterfaceWindow;
}

class ContentManagerInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ContentManagerInterfaceWindow(QWidget *parent = 0);
    ~ContentManagerInterfaceWindow();

    QPushButton* getManageTextbooksButton();
    QPushButton* getManageCoursesButton();

/*
private slots:
    void on_manageTextbooksOption_clicked();

    void on_manageCoursesOption_clicked();
*/
private:
    Ui::ContentManagerInterfaceWindow *ui;
    //ContentInputOutputManager contentIOManager;
    //ManageTextbooksInterfaceWindow manageTextbooksInterface;
};

#endif // CONTENTMANAGERINTERFACEWINDOW_H
