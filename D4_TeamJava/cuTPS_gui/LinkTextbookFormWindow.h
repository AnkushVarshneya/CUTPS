#ifndef LINKTEXTBOOKFORMWINDOW_H
#define LINKTEXTBOOKFORMWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QAbstractItemView>

namespace Ui {
class LinkTextbookFormWindow;
}

class LinkTextbookFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LinkTextbookFormWindow(QWidget *parent = 0);
    ~LinkTextbookFormWindow();

    QPushButton*    getBackButton();
    QPushButton*    getLinkTextbookButton();

    QListView*      getAllTextbooksListView();
    QListView*      getRegisteredTextbooksListView();

private:
    Ui::LinkTextbookFormWindow *ui;
};

#endif // LINKTEXTBOOKFORMWINDOW_H
