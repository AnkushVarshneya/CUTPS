#ifndef MANAGECOURSESINTERFACEWINDOW_H
#define MANAGECOURSESINTERFACEWINDOW_H

#include <QWidget>

namespace Ui {
class ManageCoursesInterfaceWindow;
}

class ManageCoursesInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageCoursesInterfaceWindow(QWidget *parent = 0);
    ~ManageCoursesInterfaceWindow();

private:
    Ui::ManageCoursesInterfaceWindow *ui;
};

#endif // MANAGECOURSESINTERFACEWINDOW_H
