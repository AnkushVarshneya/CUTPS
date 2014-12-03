#ifndef STUDENTINTERFACEWINDOW_H
#define STUDENTINTERFACEWINDOW_H

#include <QWidget>
#include "Textbook.h"
#include "OurStandardItem.h"
#include <QStandardItemModel>

namespace Ui {
class StudentInterfaceWindow;
}

class StudentInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInterfaceWindow(QWidget *parent = 0);
    ~StudentInterfaceWindow();

private slots:
    void on_viewDetailsOption_clicked();


private:
    Ui::StudentInterfaceWindow *ui;
    QStandardItemModel *treeMod;
};

#endif // STUDENTINTERFACEWINDOW_H
