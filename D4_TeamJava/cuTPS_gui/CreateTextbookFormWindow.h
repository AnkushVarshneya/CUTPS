#ifndef CREATETEXTBOOKFORMWINDOW_H
#define CREATETEXTBOOKFORMWINDOW_H

#include <QWidget>
#include "CreateChapterFormWindow.h"

#include "Textbook.h"
#include "Chapter.h"

class ManageTextbooksInterfaceWindow;

namespace Ui {
class CreateTextbookFormWindow;
}

class CreateTextbookFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTextbookFormWindow(QWidget *parent = 0);
    ~CreateTextbookFormWindow();

    ManageTextbooksInterfaceWindow *parentWindow;

private slots:
    void on_viewEditChaptersButton_clicked();

    void on_backButton_clicked();

    void on_createButton_clicked();

private:
    Ui::CreateTextbookFormWindow *ui;
    CreateChapterFormWindow createChapterForm;
};

#endif // CREATETEXTBOOKFORMWINDOW_H
