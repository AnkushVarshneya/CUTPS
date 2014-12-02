#ifndef STUDENTINTERFACEWINDOW_H
#define STUDENTINTERFACEWINDOW_H

#include <QWidget>
#include "Textbook.h"

namespace Ui {
class StudentInterfaceWindow;
}

class StudentInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInterfaceWindow(QWidget *parent = 0);
    ~StudentInterfaceWindow();

private:
    Ui::StudentInterfaceWindow *ui;
};

#endif // STUDENTINTERFACEWINDOW_H
