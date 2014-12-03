#ifndef CREATETEXTBOOKFORMWINDOW_H
#define CREATETEXTBOOKFORMWINDOW_H

#include <QWidget>
#include "EditChapterFormWindow.h"

#include "Textbook.h"
#include "Chapter.h"

#include <QPushButton>

class ManageTextbooksInterfaceWindow;

namespace Ui {
class EditTextbookFormWindow;
}

class EditTextbookFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditTextbookFormWindow(QWidget *parent = 0);
    ~EditTextbookFormWindow();

    ManageTextbooksInterfaceWindow *parentWindow;

    Ui::EditTextbookFormWindow *getUI();

    QPushButton* getBackButton();
    QPushButton* getViewEditChaptersButton();
    QPushButton* getAddChapterButton();
    QPushButton* getCreateButton();


private slots:
  /*
    void on_viewEditChaptersButton_clicked();

    void on_createButton_clicked();
*/
private:
    Ui::EditTextbookFormWindow *ui;
    EditChapterFormWindow editChapterForm;
};

#endif // CREATETEXTBOOKFORMWINDOW_H
