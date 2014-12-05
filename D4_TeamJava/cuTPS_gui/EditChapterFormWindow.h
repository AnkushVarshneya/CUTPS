#ifndef CREATECHAPTERFORMWINDOW_H
#define CREATECHAPTERFORMWINDOW_H

#include <QWidget>
#include "EditSectionFormWindow.h"
#include <QPushButton>

class EditTextbookFormWindow;

namespace Ui {
class EditChapterFormWindow;
}

class EditChapterFormWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditChapterFormWindow(QWidget *parent = 0);
    ~EditChapterFormWindow();

    QPushButton* getBackButton();
    QPushButton* getCreateButton();
    QPushButton* getCreateSectionButton();
    QPushButton* getEditSectionButton();

private:
    Ui::EditChapterFormWindow *ui;
    EditSectionFormWindow editSectionForm;
};

#endif // CREATECHAPTERFORMWINDOW_H
