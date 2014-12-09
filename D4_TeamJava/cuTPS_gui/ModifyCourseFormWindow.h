#ifndef MODIFYCOURSEFORMWINDOW_H
#define MODIFYCOURSEFORMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class ModifyCourseFormWindow;
}

class ModifyCourseFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyCourseFormWindow(QWidget *parent = 0);
    ~ModifyCourseFormWindow();

    QPushButton*    getBackButton();
    QPushButton*    getCreateButton();
    QPushButton*    getEnrollButton();
    QPushButton*    getLinkTextbookButton();

    QComboBox*      getTermComboBox();

    QLineEdit*      getCourseCodeTextBox();
    QLineEdit*      getCourseSectionTextBox();
    QLineEdit*      getInstructorTextBox();

private:
    Ui::ModifyCourseFormWindow *ui;
};

#endif // MODIFYCOURSEFORMWINDOW_H
