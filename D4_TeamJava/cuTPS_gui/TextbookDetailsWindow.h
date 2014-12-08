#ifndef TEXTBOOKDETAILSWINDOW_H
#define TEXTBOOKDETAILSWINDOW_H

#include <QtGui>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>
#include <QTreeView>
#include "Textbook.h"
#include <QDebug>
#include <QStandardItemModel>
#include "OurStandardItem.h"

namespace Ui {
class TextbookDetailsWindow;
}

class TextbookDetailsWindow : public QWidget
{
    Q_OBJECT

public:
    static TextbookDetailsWindow*   getInstance(); //singleton pattern

    explicit TextbookDetailsWindow(QWidget *parent = 0);
    explicit TextbookDetailsWindow(Textbook &textbook, QWidget *parent = 0);
    TextbookDetailsWindow(Textbook &textbook, QModelIndex idx, QStandardItemModel *model, QWidget *parent = 0);
    ~TextbookDetailsWindow();

    void                                setTextbookAndModel(Textbook &textbook, QModelIndex idx, QStandardItemModel *model);

    QPushButton*                        getAddSelectedItemOption();
    QPushButton*                        getCloseOption();
    QToolButton*                        getAddCurrentTextbookOption();
    QTreeView*                          getChaptersAndSectionsView();
private:
    Ui::TextbookDetailsWindow           *ui;
    static TextbookDetailsWindow*       instance;
};

#endif // TEXTBOOKDETAILSWINDOW_H
