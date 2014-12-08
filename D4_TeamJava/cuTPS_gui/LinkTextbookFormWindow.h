#ifndef LINKTEXTBOOKFORMWINDOW_H
#define LINKTEXTBOOKFORMWINDOW_H

#include <QWidget>

namespace Ui {
class LinkTextbookFormWindow;
}

class LinkTextbookFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LinkTextbookFormWindow(QWidget *parent = 0);
    ~LinkTextbookFormWindow();

private:
    Ui::LinkTextbookFormWindow *ui;
};

#endif // LINKTEXTBOOKFORMWINDOW_H
