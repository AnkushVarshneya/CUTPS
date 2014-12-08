#ifndef MODIFYCOURSEFORMWINDOW_H
#define MODIFYCOURSEFORMWINDOW_H

#include <QWidget>

namespace Ui {
class ModifyCourseFormWindow;
}

class ModifyCourseFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyCourseFormWindow(QWidget *parent = 0);
    ~ModifyCourseFormWindow();

private:
    Ui::ModifyCourseFormWindow *ui;
};

#endif // MODIFYCOURSEFORMWINDOW_H
