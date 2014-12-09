#ifndef MANAGECOURSESINTERFACEWINDOW_H
#define MANAGECOURSESINTERFACEWINDOW_H
#include <QPushButton>
#include <QWidget>
#include <QComboBox>

namespace Ui {
class ManageCoursesInterfaceWindow;
}

class ManageCoursesInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManageCoursesInterfaceWindow(QWidget *parent = 0);
    ~ManageCoursesInterfaceWindow();


    QPushButton* getBackButton();
    QPushButton* getCreateCourseButton();
    QPushButton* getEditCourseButton();
    QPushButton* getDeleteCourseButton();
    QComboBox*   getTermSelectOption();

    QAbstractItemView* getCourseListView();
    QAbstractItemView* getAssignedTextbooksListView();

private:
    Ui::ManageCoursesInterfaceWindow *ui;

};

#endif // MANAGECOURSESINTERFACEWINDOW_H
