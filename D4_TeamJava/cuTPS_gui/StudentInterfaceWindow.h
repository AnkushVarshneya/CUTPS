#ifndef STUDENTINTERFACEWINDOW_H
#define STUDENTINTERFACEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include "Textbook.h"
#include "OurStandardItem.h"
#include <QStandardItemModel>
#include <QTreeView>

namespace Ui {
class StudentInterfaceWindow;
}

class StudentInterfaceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentInterfaceWindow(QWidget *parent = 0);
    ~StudentInterfaceWindow();
    QPushButton*        getViewDetailsOption();
    QPushButton*        getAddTextbookOption();
    QPushButton*        getViewCartOption();
    QComboBox*          getTermSelectOption();
    QSpinBox*           getQuantityOption();
    QTreeView*          getCourseTreeView();

    void                setViewModel(QAbstractItemView *view, QStandardItemModel *mod);


private slots:



private:
    Ui::StudentInterfaceWindow *ui;
   // QStandardItemModel *treeMod;
};

#endif // STUDENTINTERFACEWINDOW_H
