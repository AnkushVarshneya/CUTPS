#ifndef STUDENTINTERFACEWINDOW_H
#define STUDENTINTERFACEWINDOW_H

#include <QWidget>
#include <QtGui>
#include <QStatusBar>
#include <QDockWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include "Textbook.h"
#include "OurStandardItem.h"
#include <QStandardItemModel>
#include <QTreeView>
#include <QListView>
#include "StudentShopView.h"
#include <QSize>


namespace Ui {
class StudentInterfaceWindow;
}

class StudentInterfaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentInterfaceWindow(QMainWindow *parent = 0);
    ~StudentInterfaceWindow();
    QStatusBar*         getStatusBar();
    QPushButton*        getViewDetailsOption();
    QPushButton*        getAddTextbookOption();
    QPushButton*        getViewCartOption();
    QComboBox*          getTermSelectOption();
    QSpinBox*           getQuantityOption();
    QTreeView*          getCourseTreeView();
    //QTreeView*          getChaptersAndSectionsTreeView();
    QListView*          getCourseView();

    void                setViewModel(QAbstractItemView *view, QStandardItemModel *mod);
    void                createDockWindow(QWidget *widget);

public slots:
    void                shrink();
private:
    Ui::StudentInterfaceWindow *ui;
    StudentShopView        *shopView;
    QDockWidget            *dock;
    void                   createStatusBar();


   // QStandardItemModel *treeMod;
};

#endif // STUDENTINTERFACEWINDOW_H
