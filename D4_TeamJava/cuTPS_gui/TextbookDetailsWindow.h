#ifndef TEXTBOOKDETAILSWINDOW_H
#define TEXTBOOKDETAILSWINDOW_H

#include <QWidget>
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
    explicit TextbookDetailsWindow(QWidget *parent = 0);
    explicit TextbookDetailsWindow(Textbook &textbook, QWidget *parent = 0);
    TextbookDetailsWindow(Textbook &textbook, QModelIndex idx, QStandardItemModel *model, QWidget *parent = 0);
    ~TextbookDetailsWindow();

private:
    Ui::TextbookDetailsWindow *ui;
    QStandardItemModel  *chaptersAndSectionsModel;
};

#endif // TEXTBOOKDETAILSWINDOW_H
