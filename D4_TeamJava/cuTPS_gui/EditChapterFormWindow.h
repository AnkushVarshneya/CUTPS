#ifndef CREATECHAPTERFORMWINDOW_H
#define CREATECHAPTERFORMWINDOW_H

#include <QWidget>
#include "EditSectionFormWindow.h"

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

    EditTextbookFormWindow *parentWindow;

private slots:

    void on_viewEditSectionButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::EditChapterFormWindow *ui;
    EditSectionFormWindow editSectionForm;
};

#endif // CREATECHAPTERFORMWINDOW_H
