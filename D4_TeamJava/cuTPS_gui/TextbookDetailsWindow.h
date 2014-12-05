#ifndef TEXTBOOKDETAILSWINDOW_H
#define TEXTBOOKDETAILSWINDOW_H

#include <QWidget>

namespace Ui {
class TextbookDetailsWindow;
}

class TextbookDetailsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TextbookDetailsWindow(QWidget *parent = 0);
    ~TextbookDetailsWindow();

private:
    Ui::TextbookDetailsWindow *ui;
};

#endif // TEXTBOOKDETAILSWINDOW_H
