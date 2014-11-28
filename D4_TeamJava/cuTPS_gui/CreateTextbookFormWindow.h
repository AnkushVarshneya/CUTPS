#ifndef CREATETEXTBOOKFORMWINDOW_H
#define CREATETEXTBOOKFORMWINDOW_H

#include <QWidget>
#include "CreateChapterFormWindow.h"

namespace Ui {
class CreateTextbookFormWindow;
}

class CreateTextbookFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTextbookFormWindow(QWidget *parent = 0);
    ~CreateTextbookFormWindow();

private slots:
    void on_viewEditChaptersButton_clicked();

private:
    Ui::CreateTextbookFormWindow *ui;
    CreateChapterFormWindow createChapterForm;
};

#endif // CREATETEXTBOOKFORMWINDOW_H
