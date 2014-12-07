#ifndef STUDENTSHOPVIEW_H
#define STUDENTSHOPVIEW_H

#include <QWidget>
#include <QtGui>
#include <QTreeView>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QListView>
#include <QPixmap>
#include <QIcon>

namespace Ui {
class StudentShopView;
}

class StudentShopView : public QWidget
{
    Q_OBJECT

public:
    explicit StudentShopView(QWidget *parent = 0);
    ~StudentShopView();
    QPushButton*        getViewDetailsOption();
    QPushButton*        getAddTextbookOption();
    QPushButton*        getViewCartOption();
    QComboBox*          getTermSelectOption();
    QSpinBox*           getQuantityOption();
    QTreeView*          getCourseTreeView();
    QListView*          getCourseView();

    void                setViewModel(QAbstractItemView *view, QStandardItemModel *mod);

private:
    Ui::StudentShopView *ui;
};

#endif // STUDENTSHOPVIEW_H
