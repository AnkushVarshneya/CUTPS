#ifndef LINKSTUDENTFORMWINDOW_H
#define LINKSTUDENTFORMWINDOW_H

#include <QWidget>

namespace Ui {
class LinkStudentFormWindow;
}

class LinkStudentFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LinkStudentFormWindow(QWidget *parent = 0);
    ~LinkStudentFormWindow();

private:
    Ui::LinkStudentFormWindow *ui;
};

#endif // LINKSTUDENTFORMWINDOW_H
